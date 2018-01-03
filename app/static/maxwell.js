"use strict";

var mic;

/*
Convert a Float32Array to a 16bit mono PCM Blob of type "audio/raw".
*/
function floatTo16bitPCM(f32array)
{
	const pcm = new ArrayBuffer(f32array.length * 2);
	const pcm_view = new DataView(pcm);
	for (var i = 0; i < f32array.length; ++i) {
		var s = Math.max(-1, Math.min(1, f32array[i]));
		pcm_view.setInt16(i * 2, s * (s < 0 ? 0x8000 : 0x7FFF), true);
	}
	return new Blob([pcm_view], {type: "audio/raw"});
}

/*
Convert audio Blob (of any format decodable by the browser) to a 16bit mono PCM blob
returns a promise.
*/
function audioTo16bitPCM(blob) {
	return new Promise((resolve, reject) => {
		const reader = new FileReader();
		reader.onload = () => {
			new OfflineAudioContext(1, reader.result.byteLength / 4, 16000)
			.decodeAudioData(reader.result)
			.then((audio) => {
				resolve(floatTo16bitPCM(audio.getChannelData(0)));
			})
			.catch(error);
		}
		reader.onerror = reject;
		reader.readAsArrayBuffer(blob);
	});
}

/*
Record from mic and send a 16bit mono PCM Blob to the server when each recording ends.
*/
navigator.mediaDevices.getUserMedia({audio: true})
.then(stream => {
	mic = new MediaRecorder(stream);
	mic.ondataavailable = audio_event => {
		audioTo16bitPCM(audio_event.data)
		.then((raw_audio) => {
			$.post("/", "audio/raw", raw_audio, () => {
				actions.status("Talk to Max");
			})
		})
		.catch(error);
	}
	document.addEventListener("keydown", e => {
		if (e.key === " ")
			recordStart();
	})
	document.addEventListener("keyup", e => {
		if (e.key === " ")
			recordStop();
	})
})
.catch(error);

function recordStart() {
	if (mic && mic.state === "inactive") {
		mic.start();
		actions.status("Listening");
	}
}

function recordStop() {
	if (mic && mic.state === "recording") {
		mic.stop();
		actions.status("...");
	}
}

function formatResponse(txt) {
	if (txt != "") {
		if (txt.indexOf("what") != -1 || txt.indexOf("how") != -1 || txt.indexOf("where") != -1 || txt.indexOf("what") != -1)
			txt = txt + "?"
		else
			txt = txt + "."
		txt = txt[0].toUpperCase() + txt.substring(1);
	}
	return txt;
}

function error(err) {
	console.warn(err.message || err);
	actions.status(err.message);
}

function oneOf(array) {
	return array[Math.floor(Math.random() * array.length)];
}

function speak(txt) {
	const say = new SpeechSynthesisUtterance(txt);
	speechSynthesis.speak(say);
}

const timerSound = new Audio(["static/timer.ogg"]);
const silverHammer = new Audio(["static/maxwells_silver_hammer.opus"]);

function notify(title, body, icon) {
	const n = new Notification(title, {body: body, icon: icon, badge: icon, silent: true});
}

Notification.requestPermission();

// Commands

function commandClear() {
	actions.logClear();
	localStorage.removeItem("log");
	return null;
}

function commandGreet() {
	return oneOf(["Hello.", "Greetings."]);
}

function getTimeFormatted(t) {
	const time = t==undefined ? new Date() : new Date(t);
	const hours = time.getHours() % 12 || 12;
	var minutes = time.getMinutes();
	const ext = (((time.getHours()*100) + minutes) > 1200) ? "pm" : "am";
	minutes = minutes < 10 ? "0" + minutes : minutes;
	return hours + ":" + minutes + ext;
}

function commandTime() {
	return (getTimeFormatted());
}

function commandTimer() {
	setTimeout(function() {
		notify("Timer", "Time's Up!", "/static/timer.svg")
		timerSound.play()
	}, 30000);
	return ("Timer set for thirty seconds.")
}

function commandMusicPlay() {
	silverHammer.play()
	return ("Playing music..")
}

function commandMusicStop() {
	silverHammer.pause()
	return ("Stopping music..")
}

const NOT_FOUND = [
	"Regrettably I can't serve you in this matter.",
	"I didn't get that.",
	"I'm not sure what you mean?"
]

const DEF = [
	["hey", "hello", "hi", "max", "hey max", "hello max", "maxwell", commandGreet],
	["clear session", "delete history", commandClear],
	["what time is it", "what is time", "what is the time", commandTime],
	["time are", "timer", commandTimer],
	["play music", commandMusicPlay],
	["stop music", commandMusicStop]
]

const COMMANDS = {};

for (var i = 0; i < DEF.length; ++i) {
	for (var j = 0; j < DEF[i].length - 1; ++j) {
		COMMANDS[DEF[i][j]] = DEF[i][DEF[i].length - 1];
	}
}

function parseCommand(command) {
	if (command in COMMANDS) {
		return COMMANDS[command](command);
	}
	return oneOf(NOT_FOUND);
}

/*
Listen for server response
*/

const ev = new EventSource("response");
ev.onmessage = e => {
	const response = JSON.parse(e.data);
	if (typeof response === "string") {
		if (response !== "") {
			actions.logUser(formatResponse(response));
		}
	}
	else {
		if (response[0]) {
			if (response[1].startsWith("search"))
				response[1] = "Search.."
			if (response[1].startsWith("note"))
				response[1] = "Saving note to your email.."
			actions.log(response[1]);
			speak(response[1]);
		}
		else {
			const txt = parseCommand(response[1]);
			if (txt !== null) {
				actions.log(txt);
				speak(txt);
			}
		}
	}
}

window.onbeforeunload = () => {
	ev.close();
}
