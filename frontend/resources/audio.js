var audio;

navigator.mediaDevices.getUserMedia({audio: true})
	.then(function (stream) {
		audio = new MediaRecorder(stream);
		audio.ondataavailable = function(e) {
			$.post("http://localhost:5000/upload", e.data, "audio/ogg", (r) => {
				console.log("Audio post status: " + r.status);
				console.log(r.responseText);
			});
		};
	})
	.catch(function(err) {console.log(err)});

document.addEventListener("keydown", (e) => {
	const key = e.key;
	if (key === ' ' && audio.state === "inactive")
		audio.start();
		return ;
	}
)

document.addEventListener("keyup", (e) => {
	const key = e.key;
	if (key === ' ' && audio.state === "recording")
		audio.stop();
	}
)
