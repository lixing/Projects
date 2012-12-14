using System;
using System.Collections.Generic;

using System.Text;

namespace BankSystem
{
    class Account
    {
        private string _CustomerNumber;

        public string CustomerNumber
        {
            get { return _CustomerNumber; }
            set { _CustomerNumber = value; }
        }

        private string _AccountNumber="";

        public string AccountNumber
        {
            get { return _AccountNumber; }
            set { _AccountNumber = value; }
        }

        private string _Type = "Savings";

        public string AccountType
        {
            get { return _Type; }
            set { _Type = value; }
        }

        private float _Amount = 0;

        public float Amount
        {
            get { return _Amount; }
            set { _Amount = value; }
        }

        public Account(string Number,string AccountNumber, string AccountType, float Amount)
        {
            _CustomerNumber = Number;
            _AccountNumber = AccountNumber;
            _Type = AccountType;
            _Amount = Amount;

        }
    }
}
