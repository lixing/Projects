using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace BankSystem
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        private CustomerController customer_control;
        private AccountController account_control;
        private int x;
        private int y;
     

        public void ShowMsgPanel(string title, string text)
        {
            groupMsg.Text = title;
            rtb_msg.Text = text;
            groupMsg.BringToFront();
            groupMsg.Location = new Point(237, 6);
        }

        public void ResetGroupBoxContainer()
        {

        }

        public void ShowPanel(int index)
        {
            ResetGroupBoxContainer();
            switch (index)
            {
                case 0:                
                    groupMain.BringToFront();
                    groupMain.Location = new Point(237, 6);
                    break;
                case 1:
                    groupSearch.BringToFront();
                    groupSearch.Location = new Point(237, 6);
                    break;
                case 2:
                    groupAdd.BringToFront();
                    groupAdd.Location = new Point(237, 6);

                    break;
                case 3:
                    groupSetup.BringToFront();
                    groupSetup.Location = new Point(237, 6);
                    break;
                case 4:
                    groupDeposit.BringToFront();
                    groupDeposit.Location = new Point(237, 6);
                    break;
                case 5:
                    groupWithdrawal.BringToFront();
                    groupWithdrawal.Location = new Point(237, 6);
                    break;

            }
        }

        public bool IsNumber(string str)
        {
            try
            {
                float i = Convert.ToSingle(str);
                return (true);
            }
            catch
            {
                return (false);
            }
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            treeViewMain.ExpandAll();
            customer_control = new CustomerController("customer.xml");
            account_control = new AccountController("account.xml");
            ShowPanel(0);
        }

        private void FormMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            if (txtAddFirstName.Text.Trim().Length == 0 || txtAddLastName.Text.Trim().Length == 0 || txtAddFirstName.Text.Trim().Length > 10 || txtAddLastName.Text.Trim().Length > 10)
            { MessageBox.Show("You must input a vaild Name!"); return; }

            if (txtAddAddress.Text.Trim().Length > 20)
            { MessageBox.Show("You must input a vaild Address! Your address should be less than 20 chars."); return; }

            if (txtAddCity.Text.Trim().Length > 15)
            { MessageBox.Show("You must input a vaild city! Your city name should be less than 15 chars."); return; }

            if (txtAddState.Text.Trim().Length > 10)
            {
                MessageBox.Show("You must input a vaild State! Your state name should be less than 10 chars."); return;
            }
            if (txtAddZIP.Text.Trim().Length > 10)
            { MessageBox.Show("You must input a vaild zip code! Your zip should be less than 10 chars."); return; }

            if (txtAddEmail.Text.Trim().Length > 36 || txtAddEmail.Text.Trim().Length == 0)
            { MessageBox.Show("You must input a vaild E-Mail!"); return; }

            if (txtAddHomePhone.Text.Trim().Length > 12)
            {
                { MessageBox.Show("You must input a vaild Home Phone!"); return; }
            }
            if (ContainLetter(txtAddCellPhone.Text) == true || txtAddCellPhone.Text.Trim().Length > 11||  txtAddCellPhone.Text.Trim().Length == 0)
            {
                { MessageBox.Show("You must input a vaild Cell Phone!"); return; }
            }




            string newnumber;
            newnumber = customer_control.AddCustomer(txtAddFirstName.Text, txtAddLastName.Text, txtAddAddress.Text,
                txtAddCity.Text, txtAddState.Text, txtAddZIP.Text, txtAddEmail.Text, txtAddHomePhone.Text,
                txtAddCellPhone.Text);

            string text = "First Name: " + txtAddFirstName.Text + Environment.NewLine;
            text += "Last Name: " + txtAddLastName.Text + Environment.NewLine;
            if (!txtAddAddress.Text.Equals(""))
                text += "Address: " + txtAddAddress.Text + Environment.NewLine;
            if (!txtAddCity.Text.Equals(""))
                text += "City: " + txtAddCity.Text + Environment.NewLine;
            if (!txtAddState.Text.Equals(""))
                text += "State: " + txtAddState.Text + Environment.NewLine;
            if (!txtAddZIP.Text.Equals(""))
                text += "Zip: " + txtAddZIP.Text + Environment.NewLine;
            text += "Email: " + txtAddEmail.Text + Environment.NewLine;
            if (!txtAddHomePhone.Text.Equals(""))
                text += "Home Phone: " + txtAddHomePhone.Text + Environment.NewLine;
            text += "Cell Phone: " + txtAddCellPhone.Text + Environment.NewLine;
            text += "-->Your Customer ID is : " + newnumber;

            ShowMsgPanel("Add Customer successful !", text);
            button1.Text = "New Account Setup";
            button1.Visible = true;
            txtAddFirstName.Clear();
            txtAddLastName.Clear();
            txtAddAddress.Clear(); txtAddCity.Clear(); txtAddState.Clear();
            txtAddZIP.Clear(); txtAddEmail.Clear(); txtAddHomePhone.Clear();
            txtAddCellPhone.Clear();


        }

        private void treeViewMain_AfterSelect(object sender, TreeViewEventArgs e)
        {
            ShowPanel(treeViewMain.SelectedNode.Index);
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {

            if (txtFirstName_Search.Text.Trim().Length == 0 || txtLastName_Search.Text.Trim().Length == 0)
            {
                MessageBox.Show("You must input valid Name to search!"); return;
            }
            dgvSearch.DataSource = customer_control.GetCustomerDataTable(txtFirstName_Search.Text, txtLastName_Search.Text);
            try
            {
                string a = dgvSearch.Rows[0].Cells[0].Value.ToString();
                if (a.Equals(""))
                    x = 0;
                else x = 1;
                y = dgvSearch.Rows.Count;
            }
            catch (Exception) {
                MessageBox.Show("No suitable data!");

            }
        }





        private void btnSubmit_Withdrawal_Click(object sender, EventArgs e)
        {
            if (account_control.AccountIsExsit(txtNumber_Withdrawal.Text) == false)
            {
                MessageBox.Show("Error : Account is not Exsits!"); return;
            }
            if (txtNumber_Withdrawal.Text.Trim().Length > 10)
            {
                MessageBox.Show("Error : Account should be less than 10 chars!"); return;
            }
            if (IsNumber(txtAmount_Withdrawal.Text) == false)
            {
                MessageBox.Show("Error : You must input a valid Amount!"); return;
            }

            if (txtAmount_Withdrawal.Text.Trim().Length > 10 || Convert.ToInt32(txtAmount_Withdrawal.Text) <= 0)
            {
                MessageBox.Show("Error : Amount should be more than 0 and less than 10,000,000,000!"); return;
            }

            Account a = account_control.GetAccount(txtNumber_Withdrawal.Text);

            float oldamount = a.Amount;

            if (account_control.Withdrawal(txtNumber_Withdrawal.Text, Convert.ToInt32(txtAmount_Withdrawal.Text)) == true)
            {
                if (chkPrint_Withdrawal.Checked == true)
                {
                    string text = "";
                    text = "Account Number : B" + txtNumber_Withdrawal.Text + Environment.NewLine;
                    text += "Withdraw Amount : " + txtAmount_Withdrawal.Text + Environment.NewLine;
                    text += "Account old Balance : " + Environment.NewLine;
                    text += Convert.ToString(oldamount) + Environment.NewLine;

                    float newamount = oldamount - float.Parse(txtAmount_Withdrawal.Text);
                    text += "Account new Balance : " + Environment.NewLine;
                    text +=  Convert.ToString(newamount) + Environment.NewLine;
                    ShowMsgPanel("Withdrawal succesful!", text);
                    button1.Text = "Withdraw again";
                    button1.Visible = true;
                }
                else
                {
                    string text = "";
                    text = "Account Number : B" + txtNumber_Withdrawal.Text + Environment.NewLine;

                    text += "WithDraw Amount: " + txtAmount_Withdrawal.Text + Environment.NewLine;
                    ShowMsgPanel("Withdrawal succesful!", text);
                    button1.Text = "Withdraw again";
                    button1.Visible = true;
                }
                txtAmount_Withdrawal.Clear();
                txtNumber_Withdrawal.Clear();
            }
            else MessageBox.Show("You have not enough money!");


        }

        private void btnCancel_Deposit_Click(object sender, EventArgs e)
        {
            txtNumber_Deposit.Clear();
            txtAmount_Deposit.Clear();
        }




        private void btnSubmit_Deposit_Click(object sender, EventArgs e)
        {
            if (account_control.AccountIsExsit(txtNumber_Deposit.Text) == false)
            {
                MessageBox.Show("Error : Account is not Exsits!"); return;
            }
            if (txtNumber_Deposit.Text.Trim().Length > 10)
            {
                MessageBox.Show("Error : Account should be less than 10 chars!"); return;
            }
            if (IsNumber(txtAmount_Deposit.Text) == false)
            {
                MessageBox.Show("Error : You must input a valid Amount!"); return;
            }

            if (txtAmount_Deposit.Text.Trim().Length > 10 || Convert.ToInt32(txtAmount_Deposit.Text) <= 0)
            {
                MessageBox.Show("Error : Amount should be more than 0 and less than 10,000,000,000!"); return;
            }

            Account a = account_control.GetAccount(txtNumber_Deposit.Text);


           float oldamount = a.Amount;

            if (account_control.Deposit(txtNumber_Deposit.Text, Convert.ToInt32(txtAmount_Deposit.Text)) == true)
            {
                if (chkPrint_Deposit.Checked == true)
                {

                    string text = "";
                    text = "Account Number : B" + txtNumber_Deposit.Text + Environment.NewLine;
                    text += "Deposit Amount : " + txtAmount_Deposit.Text + Environment.NewLine;
                    text += "Account old Balance : " + Environment.NewLine;
                    text += Convert.ToString(oldamount) + Environment.NewLine;
                    float newamount = float.Parse(txtAmount_Deposit.Text) + oldamount;
                    text += "Account new Balance : "  + Environment.NewLine;
                    text += Convert.ToString(newamount) + Environment.NewLine;

                    ShowMsgPanel("Deposit succesful", text);
                    button1.Text = "Deposit again";
                    button1.Visible = true;
                }
                else
                {
                    string text = "";
                    text = "Account Number : B" + txtNumber_Deposit.Text + Environment.NewLine;
                    text += "Deposit Amount : " + txtAmount_Deposit.Text + Environment.NewLine;
                    ShowMsgPanel("Deposit succesful!", text);
                    button1.Text = "Deposit again";
                    button1.Visible = true;
                }
                txtAmount_Deposit.Clear();
                txtNumber_Deposit.Clear();
            }

        }

        private void btnOK_Msg_Click(object sender, EventArgs e)
        {
            ShowPanel(0);
        }

        public bool ContainLetter(string str)
        {
            string temp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            for (int i = 0; i < str.Length; i++)
            {
                if (temp.ToUpper().Contains(str[i].ToString().ToUpper()) == true)
                    return true;
            }
            return false;
        }

        private void btnCancel_Withdrawal_Click(object sender, EventArgs e)
        {
            txtAmount_Withdrawal.Clear();
            txtNumber_Withdrawal.Clear();

        }

        private void lstType_SelectedIndexChanged(object sender, EventArgs e)
        {


        }

        private void btnSubmit_Setup_Click(object sender, EventArgs e)
        {


            if (rbExistngCustomer.Checked == true)
            {
                if (!lstType.Text.Equals(""))
                {

                    account_control.CurrentAccountType = lstType.Text;
                    groupLinkTo.BringToFront();
                    groupLinkTo.Location = new Point(237, 6);
                }
                else MessageBox.Show("You need to choose an account type!");

            }

            if (rbNewCustomer.Checked == true)
            {
                ShowPanel(2);
            }
        }


        private void btnLinkTo_Click(object sender, EventArgs e)
        {
            
            if (ContainLetter(textBox1.Text) == true || textBox1.Text.Trim().Length > 10)
            {
                { MessageBox.Show("You must input a vaild Account Number!"); return; }
            }

            if (txtID_Link.Text.Trim().Length == 0)
            {
                MessageBox.Show("You must input a valid Customer ID!"); return;
            }
            if (customer_control.CustomerExsit(txtID_Link.Text) == false)
            {
                MessageBox.Show("The Customer is not exsited!"); return;
            }
            if (account_control.AccountIsExsit(textBox1.Text) == true)
            {
                MessageBox.Show("The Account is  exsited! Please type another account number"); return;
            }

            account_control.AddAccount(txtID_Link.Text, textBox1.Text, account_control.CurrentAccountType, 0);
            account_control.SetAccountType(txtID_Link.Text, textBox1.Text, account_control.CurrentAccountType);
            account_control = new AccountController("account.xml");
            string text = "";
            text = "Customer ID A: " + txtID_Link.Text + Environment.NewLine;
            text += "Account Number : B" + textBox1.Text + Environment.NewLine;
            text += "Account Type : " + account_control.CurrentAccountType + Environment.NewLine;
            ShowMsgPanel("New Account Setup Successfully", text);
            button1.Text = "Regular Deposit";
            button1.Visible = true;



        }

        private void btnAddCancel_Click(object sender, EventArgs e)
        {
            ShowPanel(0);
            txtAddFirstName.Clear();
            txtAddLastName.Clear();
            txtAddAddress.Clear(); txtAddCity.Clear(); txtAddState.Clear();
            txtAddZIP.Clear(); txtAddEmail.Clear(); txtAddHomePhone.Clear();
            txtAddCellPhone.Clear();

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (button1.Text.Equals("New Account Setup"))
                ShowPanel(3);
            if (button1.Text.Equals("Regular Deposit"))
                ShowPanel(4);
            if (button1.Text.Equals("Deposit again"))
                ShowPanel(4);
            if (button1.Text.Equals("Withdraw again"))
                ShowPanel(5);
            button1.Visible = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (x == 0)
                MessageBox.Show("Invaild update!");
            else if (x == 1)
            {
                for (int i = 0; i < y; i++)
                {
                    try
                    {
                        string a = dgvSearch.Rows[i].Cells[0].Value.ToString();
                        string b = dgvSearch.Rows[i].Cells[1].Value.ToString();
                        string c = dgvSearch.Rows[i].Cells[2].Value.ToString();
                        string d = dgvSearch.Rows[i].Cells[3].Value.ToString();
                        string n = dgvSearch.Rows[i].Cells[4].Value.ToString();
                        string f = dgvSearch.Rows[i].Cells[5].Value.ToString();
                        string g = dgvSearch.Rows[i].Cells[6].Value.ToString();
                        string h = dgvSearch.Rows[i].Cells[7].Value.ToString();
                        string o = dgvSearch.Rows[i].Cells[8].Value.ToString();
                        string j = dgvSearch.Rows[i].Cells[9].Value.ToString();
                    
                   
                    
                    if (Check(a,b,c,d,n,f,g,h,o,j)==true)
                        customer_control.UpdateSearch(a, b, c, d, n, f, g, h, o, j);
                        }
                    catch (Exception) {
                        MessageBox.Show("Update successfully!");
                    }
                   
                }
            }
        }




        public Boolean Check(string a, string b, string c, string d, string n, string f, string g, string h, string o, string j)
        {
             if (b.Trim().Length == 0 || c.Trim().Length == 0 || c.Trim().Length > 10 || b.Trim().Length > 10)
                    { MessageBox.Show("You must input a vaild Name!"); 
                        return false; }
                    if (d.Trim().Length > 20)
                    { MessageBox.Show("You must input a vaild Address! Your address should be less than 20 chars."); return false; }
                    if (n.Trim().Length > 15)
                    { MessageBox.Show("You must input a vaild city! Your city name should be less than 15 chars."); return false; }
                    if (f.Trim().Length > 10)
                    {
                        MessageBox.Show("You must input a vaild State! Your state name should be less than 10 chars."); return false;
                    }
                    if (g.Trim().Length > 10)
                    { MessageBox.Show("You must input a vaild zip code! Your zip should be less than 10 chars."); return false; }
                    if (h.Trim().Length > 36 || h.Trim().Length == 0)
                    { MessageBox.Show("You must input a vaild zip code!"); return false; }

                    if (o.Trim().Length > 12)
                    {
                        { MessageBox.Show("You must input a vaild Home Phone!"); return false; }
                    }
                    if (ContainLetter(j) == true && j.Trim().Length > 11 && j.Trim().Length == 0)
                    {
                        { MessageBox.Show("You must input a vaild Cell Phone!"); return false; }
                    }
              
                    
        return true;
        }

        private void dgvSearch_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (txtFirstName_Search.Text.Trim().Length == 0 || txtLastName_Search.Text.Trim().Length == 0)
            {
                MessageBox.Show("You must input valid Name!"); return;
            }
            if(x==0)
            {
                MessageBox.Show("No suitable data!"); return;
            }

            String str = this.dgvSearch.SelectedCells[0].Value.ToString();

            if (str.Contains("A") == false)
                str = "A" + str;
            
            string account_id=account_control.ViewAccount(str,"AccountNumber");
            
            string text = "Customer Number:"+ str+Environment.NewLine;


            
            string[] split = account_id.Split(new Char[] {','});

            foreach (string s in split)
            {

                if (s.Trim() != "")
                {
                    text += "AccountNumber: " + s + Environment.NewLine;

                    text += "Account Type : " + account_control.ViewAccount(str, "AccountType_" + s) + Environment.NewLine;
                    text += "Account Amount : " + account_control.ViewAccount(str, "Amount_" + s) + Environment.NewLine + Environment.NewLine;

                }
                else text = "No Account Record!";
            }


            
            
            ShowMsgPanel("Account Information", text);
           
        }
                   
                }




            }







        
    

