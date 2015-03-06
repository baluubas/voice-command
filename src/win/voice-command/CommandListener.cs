using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Speech.Recognition;
using System.Threading.Tasks;

namespace VoiceCommand
{
	internal class CommandListener
	{
		private SpeechRecognitionEngine recognizer;

		public CommandListener()
		{
			recognizer = new SpeechRecognitionEngine(new CultureInfo("en-US"));
			recognizer.SetInputToDefaultAudioDevice();
        }

		public void ListenFor(IEnumerable<string> cmds, ICommandReporter reporter)
		{
			Choices choiceList = new Choices();
			choiceList.Add(cmds.ToArray());
			Grammar grammar = new Grammar(choiceList);
			recognizer.LoadGrammar(grammar);
            recognizer.SpeechRecognized += (s, e) => {
                reporter.Report(e.Result.Text);
            };

			recognizer.RecognizeAsync(RecognizeMode.Multiple);
		}
	}
}
