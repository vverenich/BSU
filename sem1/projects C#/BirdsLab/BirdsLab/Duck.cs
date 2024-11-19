using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BirdsLab {
    enum Types{

    }
    class Duck:Bird {
        Types Type;
        public Duck(string n, Types t, uint a, uint w) {
            Name = n;
            Type = t;
            Age = a;
            Weight = w;
        }
    }
}
