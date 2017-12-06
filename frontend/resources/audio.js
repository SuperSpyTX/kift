var audio;

navigator.mediaDevices.getUserMedia({audio: true})
	.then(function (stream) {
		audio = new MediaRecorder(stream);
		audio.ondataavailable = function(event) {
			$.post(event.data, event.data.type, "localhost:80");
			console.log("Posted Audio.");
		};
	})
	.catch(function(err) {console.log(err)});

document.addEventListener('keydown', (event) => {
	const key = event.key;
	if (key === ' ')
		if (audio.state === "inactive")
		{
			audio.start();
			return ;
		}
		if (audio.state === "recording")
			audio.stop();
	}
)
