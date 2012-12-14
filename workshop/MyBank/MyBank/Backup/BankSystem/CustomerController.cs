using System;
using System.Collections.Generic;
using System.Text;
using System.Data;

namespace BankSystem
{

    class CustomerController
    {

        private string _XMLFile = "";
        private List<Customer> _CustomerList;
        public string CurrentAccountType = "";


        internal List<Customer> CustomerList
        {
            get { return _CustomerList; }
            set { _CustomerList = value; }
        }
        private XMLController _XMLController;

        public CustomerController(string XMLFileName)
        {
            _XMLFile = XMLFileName;

            Initialize();
        }

        public void Initialize()
        {
            _CustomerList = new List<Customer>();
            _XMLController = new XMLController(_XMLFile);
            _CustomerList.Clear();
            if (System.IO.File.Exists(_XMLFile) == true)
            {
                List<string> strs = _XMLController.ReadAllSection();
                foreach (string item in strs)
                {
                    _CustomerList.Add(GetCustomerFromNumber(item));
                }

            }

        }





        public bool CustomerExsit(string number)
        {
            if (number.Contains("A") == false)
                number = "A" + number;

            foreach (Customer item in _CustomerList)
            {
                if (item.CustomerNumber.Trim() == number.Trim()) return true;
            }
            return false;
        }



        public void UpdateToFile(Customer c)
        {
            _XMLController.Write(c.CustomerNumber, "FirstName", c.FirstName);
            _XMLController.Write(c.CustomerNumber, "LastName", c.LastName);
            _XMLController.Write(c.CustomerNumber, "Address", c.Address);
            _XMLController.Write(c.CustomerNumber, "City", c.City);
            _XMLController.Write(c.CustomerNumber, "State", c.State);
            _XMLController.Write(c.CustomerNumber, "Zip", c.ZIP);
            _XMLController.Write(c.CustomerNumber, "Email", c.Email);
            _XMLController.Write(c.CustomerNumber, "HomePhone", c.HomePhone);
            _XMLController.Write(c.CustomerNumber, "CellPhone", c.CellPhone);
  
        }

        public void UpdateAllToFile()
        {
            foreach (Customer c in _CustomerList)
            {
                _XMLController.Write(c.CustomerNumber, "FirstName", c.FirstName);
                _XMLController.Write(c.CustomerNumber, "LastName", c.LastName);
                _XMLController.Write(c.CustomerNumber, "Address", c.Address);
                _XMLController.Write(c.CustomerNumber, "City", c.City);
                _XMLController.Write(c.CustomerNumber, "State", c.State);
                _XMLController.Write(c.CustomerNumber, "Zip", c.ZIP);
                _XMLController.Write(c.CustomerNumber, "Email", c.Email);
                _XMLController.Write(c.CustomerNumber, "HomePhone", c.HomePhone);
                _XMLController.Write(c.CustomerNumber, "CellPhone", c.CellPhone);
               

            }
        }



        public string AddCustomer(string firstname, string lastname, string address, string city,
            string state, string zip, string email, string homephone, string cellphone)
        {
            
            string number = this.GenerateCustomerNumber();
            Customer c = new Customer(number,
                 firstname, lastname, address, city, state, zip, email, homephone, cellphone);
            
            _CustomerList.Add(c);
           
            UpdateToFile(c);
            return number;
        }


       

               

        

        private Customer GetCustomerFromNumber(string number)
        {
            if (number.Contains("A") == false) number = "A" + number;
            Customer c = new Customer(number,
                _XMLController.Read(number, "FirstName"),
                  _XMLController.Read(number, "LastName"),
                   _XMLController.Read(number, "Address"),
                    _XMLController.Read(number, "City"),
                     _XMLController.Read(number, "State"),
                      _XMLController.Read(number, "Zip"),
                       _XMLController.Read(number, "Email"),
                        _XMLController.Read(number, "HomePhone"),
                        _XMLController.Read(number, "CellPhone"));

            return c;

        }

        public DataTable GetCustomerDataTable(string firstname, string lastname)
        {
            DataTable dt = new DataTable("Infomation");
            dt.Columns.Add(new DataColumn("Customer Number"));
            dt.Columns.Add(new DataColumn("First Name"));
            dt.Columns.Add(new DataColumn("Last Name"));
            dt.Columns.Add(new DataColumn("Address"));
            dt.Columns.Add(new DataColumn("City"));
            dt.Columns.Add(new DataColumn("State"));
            dt.Columns.Add(new DataColumn("Zip"));
            dt.Columns.Add(new DataColumn("Email"));
            dt.Columns.Add(new DataColumn("HomePhone"));
            dt.Columns.Add(new DataColumn("CellPhone"));


            DataRow newrow;
            foreach (Customer item in _CustomerList)
            {
                if (item.FirstName.ToUpper().Trim() == firstname.ToUpper().Trim() &&
                    item.LastName.ToUpper().Trim() == lastname.ToUpper().Trim())
                {
                    newrow = dt.NewRow();
                    newrow["Customer Number"] = item.CustomerNumber.Substring(1);
                    newrow["First Name"] = item.FirstName;
                    newrow["Last Name"] = item.LastName;
                    newrow["Address"] = item.Address;
                    newrow["City"] = item.City;
                    newrow["State"] = item.State;
                    newrow["Zip"] = item.ZIP;
                    newrow["Email"] = item.Email;
                    newrow["HomePhone"] = item.HomePhone;
                    newrow["CellPhone"] = item.CellPhone;
                    
                    dt.Rows.Add(newrow);

                }
            }
            return dt;

        }

        
        public string GenerateCustomerNumber()
        {
            Random r = new Random(DateTime.Now.Millisecond);
            int number = r.Next(899999) + 10000;
            return ("A" + number.ToString());
        }



        public void UpdateSearch(string number, string a, string b, string d, string e, string f, string g, string h, string i, string j)
        {
            if (number.Contains("A") == false)
                number = "A" + number;
            
            foreach (Customer c in _CustomerList)
            {
                _XMLController.Write(number, "FirstName", a);
                _XMLController.Write(number, "LastName", b);
                _XMLController.Write(number, "Address", d);
                _XMLController.Write(number, "City", e);
                _XMLController.Write(number, "State", f);
                _XMLController.Write(number, "Zip", g);
                _XMLController.Write(number, "Email",h);
                _XMLController.Write(number, "HomePhone", i);
                _XMLController.Write(number, "CellPhone", j);
                
            }



            
        }
    }
    }


