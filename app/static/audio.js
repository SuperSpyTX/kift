"use strict";

var audio;

navigator.mediaDevices.getUserMedia({audio: true})
	.then(function (stream) {
		audio = new MediaRecorder(stream);
		audio.ondataavailable = (e) => {
			var reader = new FileReader();
			reader.onloadend = () => {
				/* Create context to sample at 16khz */
				var ctx = new OfflineAudioContext(1, reader.result.byteLength / 4, 16000);
				ctx.decodeAudioData(reader.result, (audio_buff) => {
					var samples = audio_buff.getChannelData(0);
					/* We want a 16bit output so we need two bytes per sample */
					var buff = new ArrayBuffer(samples.length * 2);
					var view = new DataView(buff);
					var offset = 0;
					for (var i = 0; i < samples.length; ++i, offset += 2) {
						var s = Math.max(-1, Math.min(1, samples[i]));
						view.setInt16(offset, s < 0 ? s * 0x8000 : s * 0x7FFF, true);
					}
					var raw_audio = new Blob([view], { type: "audio/raw"});
					$.post("/kift", "audio/raw", raw_audio, (r) => {
						console.log("Raw audio posted!");
					});
				})
			}
			reader.readAsArrayBuffer(e.data)
		};
	})
	.catch(console.log);

document.addEventListener("keydown", (e) => {
	if (e.key === ' ' && audio.state === "inactive")
		audio.start();
})

document.addEventListener("keyup", (e) => {
	if (e.key === ' ' && audio.state === "recording")
		audio.stop();
})
