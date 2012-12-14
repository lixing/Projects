using System;
using System.Collections.Generic;
using System.Text;

namespace BankSystem
{
    class Customer
    {

        private string _FirstName;

        public string FirstName
        {
            get { return _FirstName; }
            set { _FirstName = value; }
        }

        private string _LastName;

        public string LastName
        {
            get { return _LastName; }
            set { _LastName = value; }
        }
        private string _Address;

        public string Address
        {
            get { return _Address; }
            set { _Address = value; }
        }
        private string _City;

        public string City
        {
            get { return _City; }
            set { _City = value; }
        }
        private string _State;

        public string State
        {
            get { return _State; }
            set { _State = value; }
        }
        private string _ZIP;

        public string ZIP
        {
            get { return _ZIP; }
            set { _ZIP = value; }
        }
        private string _Email;

        public string Email
        {
            get { return _Email; }
            set { _Email = value; }
        }
        private string _HomePhone;

        public string HomePhone
        {
            get { return _HomePhone; }
            set { _HomePhone = value; }
        }
        private string _CellPhone;

        public string CellPhone
        {
            get { return _CellPhone; }
            set { _CellPhone = value; }
        }
        private string _CustomerNumber;

        public string CustomerNumber
        {
            get { return _CustomerNumber; }
            set { _CustomerNumber = value; }
        }





        public Customer(string Number,string firstname,string lastname,string address,string city,
            string state,string zip,string email,string homephone,string cellphone)
        {
           _CustomerNumber = Number;
         _FirstName=firstname;
        _LastName=lastname;
        _Address=address;
       _City=city;
        _State=state;
        _ZIP=zip;
        _Email=email;
        _HomePhone=homephone;
        _CellPhone=cellphone;
       

        }


        


    }
}
