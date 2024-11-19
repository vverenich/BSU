using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BirdsLab {
    enum Gender {
        "male";
        "female"
    }
    class Bird {
        public uint Age { get; set; }
        public uint Weight { get; set; }
        public string Name { get; set; } = "Unknown";
        public Gender Sex { get; set; }
    }
}
