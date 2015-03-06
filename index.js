var	spawn 	= require('child_process').spawn;
var exe = '.bin/voice-command';

function VoiceCommand(cmds) {
	if(!cmds.length) {
		throw new Error('Invalid argument. Cmds must be a string array with at least one item.');
	}
	this.cmds = cmds;
}


VoiceCommand.prototype.startListening = function() {
	if(this.childPid) {
		throw new Error('Already listening');
	}

	this.childProcess = spawn(exe, this.cmds);
};

VoiceCommand.prototype.stopListening = function() {
	if(!this.childProcess) {
		throw new Error('Not listening');
	}
	
	this.childProcess.kill();
	this.childProcess = null;
};

module.exports = VoiceCommand;