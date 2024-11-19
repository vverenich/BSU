using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace The_game {
    [Serializable]
    public class GameResult {
        public GameResult() {

        }
        public GameResult(string name, DateTime start, DateTime time, int clicks) {
            PlayerName = name;
            StartTime = start;
            Time = time;
            Clicks = clicks;
        }
        public string PlayerName { get; set; }
        public DateTime StartTime { get; set; }
        public DateTime Time { get; set; }
        public int Clicks { get; set; }
        public override string ToString() {
            return PlayerName.ToString() + ", " + "Date: "+StartTime.ToString("G") + ", " + "Time: "+Time.ToString("mm:ss") + ", " + "Clicks: "+Clicks.ToString();
        }
    }
}
