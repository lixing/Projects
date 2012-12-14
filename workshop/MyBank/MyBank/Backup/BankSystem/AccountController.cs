using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Windows.Forms;

namespace BankSystem
{

    class AccountController
    {

        private string _XMLFile = "account.xml";
        private List<Account> _AccountList;
        public string CurrentAccountType = "Savings";


        internal List<Account> AccountList
        {
            get { return _AccountList; }
            set { _AccountList = value; }
        }
        private XMLController _XMLController;

        public AccountController(string XMLFileName)
        {
            _XMLFile = XMLFileName;

            Initialize();
        }

        public void Initialize()
        {
            _AccountList = new List<Account>();
            _XMLController = new XMLController(_XMLFile);
            _AccountList.Clear();
            List<Account> list;
            if (System.IO.File.Exists(_XMLFile) == true)
            {
                List<string> strs = _XMLController.ReadAllSection();
                foreach (string item in strs)
                {
                    list = GetAccountFromNumber(item);
                    foreach (Account thing in list)
                    {

                        _AccountList.Add(thing);
                    }
                   
                }

            }

        }


        /// <summary>
        /// number 为要传入的账号
        /// </summary>
        /// <param name="number"></param>
        /// <returns></returns>
        public bool AccountIsExsit(string number)
        {
            List<string> list = _XMLController.ReadAllSection();

            if (number.Contains("B") == false)
                number = "B" + number;
     //       MessageBox.Show(number);
            _XMLFile="account.xml";
            string account_id;
            string[] split;
        //    string section;

            foreach (string temp in list)
            {
            account_id=_XMLController.Read(temp, "AccountNumber");
            split = account_id.Split(new Char[] {','});

             foreach (string s in split)
             {
                // MessageBox.Show(s);
                 if (s.Trim() != "")
                 {
                     if (s.Trim().ToUpper() .Equals( number.Trim().ToUpper()))
                         return true;
                 }
                 
            }
            return false;
            }

             return false;
            
        }


        public void UpdateToFile(Account a)
        {

            string temp = _XMLController.Read(a.CustomerNumber, "AccountNumber");

            _XMLController.Write(a.CustomerNumber, "AccountNumber", temp);
            _XMLController.Write(a.CustomerNumber, "AccountType_" + a.AccountNumber, a.AccountType);
            _XMLController.Write(a.CustomerNumber, "Amount_" + a.AccountNumber, a.Amount.ToString());
        }

   /*     public void UpdateAllToFile()
        {
            foreach (Customer c in _AccountList)
            {
                _XMLController.Write(c.AccountNumber, "AccountNumber", c.AccountNumber);
                _XMLController.Write(c.AccountNumber, "AccountType", c.AccountType);
                _XMLController.Write(c.AccountNumber, "Amount", c.Amount.ToString());

            }
        }
    * */




      


        public bool Deposit(string number, float amount)
        {
            if (number.Contains("B") == false)
                number = "B" + number;

            foreach (Account a in _AccountList)
            {
                if (a.AccountNumber == number)
                {

                    a.Amount = a.Amount + amount;
                    UpdateToFile(a);
                    return true;
                }
            }

            return false;
        }

        public bool Withdrawal(string number, float amount)
        {
            if (number.Contains("B") == false)
                number = "B" + number;
            foreach (Account a in _AccountList)
            {
                if (a.AccountNumber == number)
                {
                    if ((a.Amount - amount) < 0)
                        return false;
                    else
                    {
                        a.Amount = a.Amount - amount;
                        UpdateToFile(a);
                        return true;
                    }
                }

            }
            return false;
        }


        public void AddAccount(string number, string account_id,string account_type, float amount)
        {
            if (number.Contains("A") == false)
                number = "A" + number;
            if (account_id.Contains("B") == false)
                account_id = "B" + account_id;

            Account a = new Account(number,account_id,account_type, amount);
         
            _AccountList.Add(a);

            string temp = _XMLController.Read(a.CustomerNumber, "AccountNumber");
            if (temp.Contains(a.AccountNumber) == false)
                temp = temp + "," + a.AccountNumber.ToString();
            _XMLController.Write(a.CustomerNumber, "AccountNumber", temp);
            _XMLController.Write(a.CustomerNumber, "AccountType_" + a.AccountNumber, a.AccountType);
            _XMLController.Write(a.CustomerNumber, "Amount_" + a.AccountNumber, a.Amount.ToString());
    
           
        }



        public void SetAccountType(string customer_number, string account_number, string accounttype)
        {
            if (customer_number.Contains("A") == false)
                customer_number = "A" + customer_number;
            if (account_number.Contains("B") == false)
                account_number = "B" + account_number;

            foreach (Account a in _AccountList)
            {
                if (!_XMLController.Read(customer_number, "AccountNumber").Equals(""))
                    
                {
                    a.AccountNumber =  a.AccountNumber+"," + account_number;
                    
                  
                }
                else
                    a.AccountNumber = account_number;
                a.AccountType = accounttype;

                UpdateToFile(a);
                return;
             
            }
            return;
        }


        public Account GetAccount(string number)
        {
            if (number.Contains("B") == false)
                number = "B" + number;
            foreach (Account a in _AccountList)
            {
                if (a.AccountNumber == number)
                {
                    return a;
                }
            }
            return null;
        }


        private List<Account> GetAccountFromNumber(string number)
        {
            
            string num=_XMLController.Read(number, "AccountNumber");
             string[] split = num.Split(new Char[] {','});
             List<Account> list = new List<Account>();
             foreach (string s in split)
             {

                 if (s.Trim() != "")
                 {
                     Account a = new Account(number, s, _XMLController.Read(number, "AccountType_" + s), Convert.ToSingle(_XMLController.Read(number, "Amount_" + s)));
                     if (_XMLController.Read(number, "Amount_" + num) != string.Empty)
                     {
                         a.Amount = Convert.ToSingle(_XMLController.Read(number, "Amount_" + num));
                     }
                     list.Add(a);
                     
                 }
             }
             return list;
           

        }


        public string ViewAccount(string number,string name)
        {
            _XMLFile = "account.xml";
            string num = _XMLController.Read(number, name);
            
            return num;
        }


 
    }
}


