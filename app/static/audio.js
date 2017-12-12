"use strict";

var audio;

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
			.catch(console.warn);
		}
		reader.onerror = reject;
		reader.readAsArrayBuffer(blob);
	});
}

/*
Record from mic and send a 16bit mono PCM Blob to the server when each recording ends.
*/
navigator.mediaDevices.getUserMedia({audio: true})
.then((stream) => {
	audio = new MediaRecorder(stream);
	audio.ondataavailable = (audio_event) => {
		audioTo16bitPCM(audio_event.data)
		.then((raw_audio) => {
			$.post("/", "audio/raw", raw_audio, (r) => {
				console.log("Raw audio posted!");
			})
		})
		.catch(console.warn);
	}
	document.addEventListener("keydown", (e) => {
		if (e.key === ' ' && audio.state === "inactive") {
			audio.start();
			actions.recording(true);
		}
	})
	document.addEventListener("keyup", (e) => {
		if (e.key === ' ' && audio.state === "recording") {
			audio.stop();
			actions.recording(false);
		}
	})
})
.catch((e) => console.warn(e.message));
