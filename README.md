# voice-command

Node module for voice commands using native, offline speech recognition.

# Why

I was building a NW.js/atom-shell type of application that I wanted to be able to control using voice commands.
Naturally I tried to use `webkitSpeechRecognition` but for my particular purpose this wasn't a good fit.

First, it's not really made to support commands, is more of a dictation/free form sort of thing. So, it does not
 trigger directly on commands, it returns when it consider it to be silent again.

Second, there is no hotword support, like "ok google" that starts the voice recognization. Since my interface has no
buttons to start it with it would mean the app would be listening all the time, sending everything that is being said
 to Google servers. Which I'm guessing is not ok with them either, if you you have many people using the application.

Most platforms however, have excellent support for for speech. OSX has [NSSpeechRecognizer](https://developer.apple
.com/library/mac/documentation/Cocoa/Reference/ApplicationKit/Classes/NSSpeechRecognizer_Class/index.html) and
Windows has whole [System.Speech namespace](https://msdn.microsoft.com/en-us/library/system.speech.recognition
.speechrecognitionengine(v=vs.110).aspx) in .NET. Both are using stuff that is built in to the OS which enables
offline recognization (so it does not send audio to others), it's probably faster since you can feed the service with
 the list of commands that you are interested in (and thank to that it's probably more accurate but I might be out on
  a limb here).

# How

<pre><code>
var VoiceCommand = require('voice-command');

var voiceCommand = new VoiceCommand(['hello', 'goodbye']);
voiceCommand.on('command', function(command) {
	console.log('VOICE COMMAND: ' + command)
});
voiceCommand.startListening();


process.on('exit', function() {
	voiceCommand.stopListening();
})
</code></pre>

#Supported platforms

It should run on:

* OSX v10.3 (Panther) or later (Depends on NSSpeechRecognizer)
* Windows Vista SP2 or later

No Linux support yet but there are engines that we could use. Jasper seem to be a wrapper around different
engines and has a simple interface: https://jasperproject.github.io/

Currently I don't distribute the binaries so if you are on OSX you will need XCode in your path. Same goes for
Windows, you'll need .NET framework. When writing this I see that is not really a good idea so I'll probably change
that. 