using System;
using System.Linq;
using System.Threading;

namespace VoiceCommand
{
	class Program
	{
		static void Main(string[] args)
		{
			if (args.Length < 1)
			{
				Console.WriteLine("Usage: voice-command phrase [<phrase> ...]");
				Environment.Exit(1);
			}
			
			var cmdListener = new CommandListener();
			var cmdReporter = new StandardOutputReporter();

			cmdListener.ListenFor(args, cmdReporter);			
			Thread.Sleep(int.MaxValue);
		}
	}
}
