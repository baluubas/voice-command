var VoiceCommand = require('../index.js');

var voiceCommand = new VoiceCommand(['hello', 'goodbye']);
voiceCommand.on('command', function(command) {
	console.log('VOICE COMMAND: ' + command)
});
voiceCommand.startListening();


process.on('exit', function() {
	voiceCommand.stopListening();
})
