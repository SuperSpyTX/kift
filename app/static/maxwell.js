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
		if (txt.indexOf("what") != -1 || txt.indexOf("how") != -1)
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

// Commands

function commandClear() {
	actions.logClear();
	localStorage.removeItem("log");
	return null;
}

function commandGreet() {
	return oneOf(["Hello.", "Greetings."]);
}

const NOT_FOUND = [
	"Regrettably I can't serve you in this matter.",
	"I didn't get that.",
	"I'm not sure what you mean."
]

const COMMANDS = {
	"hey": commandGreet,
	"hello": commandGreet,
	"hey hello": commandGreet,
	"hi": commandGreet,
	"hey max": commandGreet,
	"hi max": commandGreet,
	"hello max": commandGreet,
	"max": commandGreet,
	"maxwell": commandGreet,
	"clear session": commandClear,
	"delete history": commandClear
}

function parseCommand(command) {
	if (command in COMMANDS) {
		return COMMANDS[command](command);
	}
	else
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
