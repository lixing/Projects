using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MySql.Data;
using MySql.Data.MySqlClient;
using System.Data.SqlClient;
using System.Data;
using System.Drawing;


namespace WindowsFormsApplication1
{
    public class useraction
    {
        private MySqlConnection Conn = null;
        private MySqlCommand Comm = null;
        private MySqlDataReader Reader = null;
        MySqlDataAdapter myadp; // mysql数据适配器 
        DataSet myds; // 数据集 
        public useraction()
        {
            try
            {
                MySqlConnectionStringBuilder Builder = new MySqlConnectionStringBuilder();
                Builder.Add("Database", "happydiningroom");
                Builder.Add("Data Source", "localhost");
                Builder.Add("User Id", "root");
                Builder.Add("Password", "admin");

                Conn = new MySqlConnection(Builder.ConnectionString);

                Conn.Open();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                try
                {
                    if (Conn != null)
                    {
                        Conn.Close();
                        Conn = null;
                    }
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.Message);
                }
            }
        }
        public Boolean isUserExist(String username)
        {
            try
            {
                Comm = new MySqlCommand("select * from user where userid='" + username + "'", Conn);
                Reader = Comm.ExecuteReader();

                while (Reader.Read())
                {
                    if (Reader.GetString(0).Equals(username))
                        return true;
                }
                return false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }
            finally
            {
                Reader.Close();
            }
        }
        public void dropUser()
        {
            try
            {
                if (Reader != null)
                {
                    Reader.Close();
                    Reader = null;
                }
                if (Comm != null)
                {
                    Comm.Dispose();
                    Comm = null;
                }
                if (Conn != null)
                {
                    Conn.Close();
                    Conn = null;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }



        }
        public String getUserData(int userid, String column)
        {
            try
            {

                Comm = new MySqlCommand("select * from user where userid='" + userid + "'", Conn);
                Reader = Comm.ExecuteReader();

                while (Reader.Read())
                {
                    return Reader.GetString(column);
                }

                return "error";

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return "error";
            }
            finally
            {
                Reader.Close();
            }
        }

        public string buy(string balance, int user_id, int price, int no)
        {
            int userBalance = 0;
            Comm = new MySqlCommand("select * from user where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();
            if (Reader.Read())

                userBalance = Reader.GetInt32(6) - price * no;
            Reader.Close();
            try
            {
                Comm = new MySqlCommand("update user set " + balance + "= '" + userBalance + "' where userid='" + user_id + "'", Conn);

                Comm.ExecuteNonQuery();
                return no.ToString();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return "0";

            }

        }
        public void warehousebuy(int user_id, int no, string name)
        {
            int current_amount = 1;

            try
            {

                Comm = new MySqlCommand("select * from warehouse where userid='" + user_id + "'", Conn);
                Reader = Comm.ExecuteReader();
                //System.Console.Write(Reader.GetInt32(3));
                if (Reader.Read())
                    current_amount = Convert.ToInt32(Reader.GetString(name)) + no;

                Reader.Close();

                Comm = new MySqlCommand("update warehouse set " + name + "= '" + current_amount + "' where userid='" + user_id + "'", Conn);

                Comm.ExecuteNonQuery();







            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);


            }
            finally
            {
                Reader.Close();
            }
        }
        public Boolean isaffordable(int user_id, int cost)
        {
            try
            {
                Comm = new MySqlCommand("select * from user where userid='" + user_id + "'", Conn);
                Reader = Comm.ExecuteReader();

                while (Reader.Read())
                {
                    if (Convert.ToInt32(Reader.GetString(6)) >= cost)
                        return true;
                    else return false;
                }
                return false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }
            finally
            {
                Reader.Close();
            }
        }
        public string warehouseshow(int user_id, string name)
        {
            try
            {
                Comm = new MySqlCommand("select * from warehouse where userid='" + user_id + "'", Conn);
                Reader = Comm.ExecuteReader();


                if (Reader.Read())
                    return Reader.GetString(name);
                else return "failed!";


            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return "false";
            }
            finally
            {
                Reader.Close();
            }
        }
        public Boolean login(int user_id, String password)
        {
            try
            {
                Comm = new MySqlCommand("select * from user where userid='" + user_id + "' and password='" + password + "'", Conn);
                Reader = Comm.ExecuteReader();

                while (Reader.Read())
                {
                    return true;
                }
                return false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return false;
            }
            finally
            {
                Reader.Close();
            }
        }

        public Boolean cook(int user_id, int price, string name1, string name2, string name3, string name4)
        {
            int c = 0, d = 0, e = 0, f = 0;
            if ((cookenough(user_id, name1, name2, name3) == false))
            {
                MessageBox.Show("ingrediant is not enough!");
                return false;
            }


            Comm = new MySqlCommand("select * from warehouse where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read())
            {
                c = Reader.GetInt32(name1) - 1;
                d = Reader.GetInt32(name2) - 1;
                e = Reader.GetInt32(name3) - 1;
                f = Reader.GetInt32(name4) + 1;
            }
            Reader.Close();
            Comm = new MySqlCommand("update warehouse set " + name1 + "= '" + c + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();
            Comm = new MySqlCommand("update warehouse set " + name2 + "= '" + d + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();
            Comm = new MySqlCommand("update warehouse set " + name3 + "= '" + e + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();
            Comm = new MySqlCommand("update warehouse set " + name4 + "= '" + f + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();
            return true;
        }
        public Boolean cookenough(int user_id, string name1, string name2, string name3)
        {
            int a = 0, b = 0, c = 0;
            Comm = new MySqlCommand("select * from warehouse where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read())
            {
                a = Reader.GetInt32(name1);
                b = Reader.GetInt32(name2);
                c = Reader.GetInt32(name3);
            }
            Reader.Close();
            if (a < 1 || b < 1 || c < 1)
                return false;
            else return true;
        }
        public void uplevel(int user_id)
        {

            Comm = new MySqlCommand("select * from user where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read())
            {
                double a = Reader.GetInt32(8) / 100;
                if (Math.Floor(a) > Reader.GetInt32(7))
                    Comm = new MySqlCommand("update user set skilllevel= '" + Math.Floor(a) + "' where userid='" + user_id + "'", Conn);
                Comm.ExecuteNonQuery();
                MessageBox.Show("Level Up!");
            }
            Reader.Close();

        }
        public void a(DataGridView dataGridView1,int user_id)
        {
            myadp = new MySqlDataAdapter("select userid,gender from user where userid!='" + user_id + "'", Conn);
            myds = new DataSet();
            myadp.Fill(myds, "user");
            ;
            BindingSource bindingSource1 = new BindingSource();

            bindingSource1.DataSource = myds.Tables["user"];
            dataGridView1.DataSource = bindingSource1;






        }
        public void addfriends(int user_id, string friends_id)
        {
            string a="a", b="b", c="c";
            Comm = new MySqlCommand("select * from friends where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();

            while (Reader.Read())
            {
                a = Reader.GetString(1);
                b = Reader.GetString(2);
                c = Reader.GetString(3);}
            Reader.Close();

                if (a.Equals("")==true  )
                {
                    Comm = new MySqlCommand("update friends set friend_a= '" + friends_id + "' where userid='" + user_id + "'", Conn);
                    Comm.ExecuteNonQuery();
                  
                }
                else if (b.Equals("") == true )
                {
                    Comm = new MySqlCommand("update friends set friend_b= '" + friends_id + "' where userid='" + user_id + "'", Conn);
                    Comm.ExecuteNonQuery();
                    MessageBox.Show("Add Friends Successfully!");
                }
                else if (c.Equals("") == true )
                {
                    Comm = new MySqlCommand("update friends set friend_c= '" + friends_id + "' where userid='" + user_id + "'", Conn);
                    Comm.ExecuteNonQuery();
                    MessageBox.Show("Add Friends Successfully!");
                }
                else if(a.Equals(friends_id)||b.Equals(friends_id)||c.Equals(friends_id))
                    MessageBox.Show("You have added this friend!");
                else MessageBox.Show("You have add 3 friends!");
            }
            






/*

            Comm = new MySqlCommand("update friends set friend_c= '" + friends_id + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();
            MessageBox.Show("Add Friends Successfully!");
            while (Reader.Read())
            {
                if (!Reader.GetString(1) .Equals(""))
                {
                    if (!Reader.GetString(2) .Equals(""))
                    {
                        if (!Reader.GetString(3) .Equals(""))
                            MessageBox.Show("You have 3 friends!");
                        else
                        {
                            Comm = new MySqlCommand("update friends set friend_c= '" + friends_id + "' where userid='" + user_id + "'", Conn);
                            Comm.ExecuteNonQuery();
                            MessageBox.Show("Add Friends Successfully!");
                        }
                    }
                    else
                    {
                        Comm = new MySqlCommand("update friends set friend_b= '" + friends_id + "' where userid='" + user_id + "'", Conn);
                        Comm.ExecuteNonQuery();
                        MessageBox.Show("Add Friends Successfully!");
                    }
                }
                else {
                    Comm = new MySqlCommand("update friends set friend_a= '" + friends_id + "' where userid='" + user_id + "'", Conn);
                    Comm.ExecuteNonQuery();
                    MessageBox.Show("Add Friends Successfully!");
                }

            }
            Reader.Close();*/
            


           




        
        public int dishamount(int user_id, string a)
        {
            int b = 0; string c = a + "_amount";
            Comm = new MySqlCommand("select * from warehouse where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read())
            {
                b = Reader.GetInt32(c);

            }
            Reader.Close();
            return b;
        }
        public void servefood(int user_id, string dish)
        {
            int price = 0, a = 0, b = 0, d = 0; string c = dish + "_amount";
            Comm = new MySqlCommand("select * from menu where dish_name='" + dish + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read())
            {
                price = Reader.GetInt32(1);
            }
            Reader.Close();

            Comm = new MySqlCommand("select * from user where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read())
            {
                a = Reader.GetInt32(6) + price;
                b = Reader.GetInt32(8) + 10;



            }
            Reader.Close();


            int an = Reader.GetInt32(7) + 1;

            if (Reader.GetInt32(8) % 100 == 0)
            {
                Comm = new MySqlCommand("update user set skilllevel= '" + an + "' where userid='" + user_id + "'", Conn);
                Comm.ExecuteNonQuery();
                MessageBox.Show("Level Up!");
            }
            Comm = new MySqlCommand("update user set " + "balance" + "= '" + a + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();

            Comm = new MySqlCommand("update user set " + "charmingvalue" + "= '" + b + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();
            Comm = new MySqlCommand("select * from warehouse where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();

            while (Reader.Read())
            {
                d = Reader.GetInt32(c) - 1;

            }
            Reader.Close();


            Comm = new MySqlCommand("update warehouse set " + c + "= '" + d + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();



        }
        public void fur_buy(int userid, string column, PictureBox picture, int h, string s)
        {
            int g = 0;
            Comm = new MySqlCommand("select * from furnishings where userid='" + userid + "'", Conn);
            Reader = Comm.ExecuteReader();

            if(Reader.Read())
            {
                int m = Reader.GetInt32(column);
                Reader.Close();
                if (m > 0)
                    MessageBox.Show("You have bought one!");


                else if (m == 0)
                {
                    
                    if (h < Convert.ToInt32(getUserData(userid, "balance")))
                    {
                        picture.Visible = true;


                        Comm = new MySqlCommand("select * from user where userid='" + userid + "'", Conn);
                        Reader = Comm.ExecuteReader();

                        while (Reader.Read())
                            g = Reader.GetInt32(6) - h;
                        Reader.Close();
                        Comm = new MySqlCommand("update furnishings set " + column + "= 1 where userid='" + userid + "'", Conn);
                        Comm.ExecuteNonQuery();
                        Comm = new MySqlCommand("update user set balance= '" + g + "' where userid='" + userid + "'", Conn);
                        Comm.ExecuteNonQuery();
                        MessageBox.Show("Buy " + s + " successfully!");
                    }
                    else MessageBox.Show("You don't have enough money");
                }




            }
        }
        public void fur_location(int userid, int x, int y, PictureBox pic, int amount)
        {
            Comm = new MySqlCommand("select * from furnishings where userid='" + userid + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read())
            {
                if (Reader.GetInt32(amount) > 0)
                {
                    pic.Visible = true;
                    int p = Reader.GetInt32(x);
                    int q = Reader.GetInt32(y);
                    pic.Location = new Point(p, q);
                }

            }
            Reader.Close();
        }
        public void fur_save(int user_id, int x, int y, PictureBox pic, string m, string n)
        {
            Comm = new MySqlCommand("update furnishings set " + m + "= '" + x + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();
            Comm = new MySqlCommand("update furnishings set " + n + "= '" + y + "' where userid='" + user_id + "'", Conn);
            Comm.ExecuteNonQuery();


        }
       /* public void visit_friend(int user_id, string friend_id)
        { 
            Comm = new MySqlCommand("select * from friends where userid='" + user_id + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read()) { 
                if(Reader.GetString(1).Equals(friend_id)){
                    friendshome a=new friendshome();
                a.Show();}
                else if(Reader.GetString(2).Equals(friend_id)){
                    friendshome a=new friendshome();
                a.Show();}
                else if(Reader.GetString(3).Equals(friend_id)){
                    friendshome a=new friendshome();
                a.Show();}
                else MessageBox.Show("He/She is not your friend! You need to add friend first.");

            }
            Reader.Close();
                
            }*/
        public void friendhome(int friend_id,PictureBox a,int b,int x, int y)
        {
            Comm = new MySqlCommand("select * from furnishings where userid='" + friend_id + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read()) {
                if (Reader.GetInt32(b) != 0)
                {
                    a.Location = new Point(Reader.GetInt32(x), Reader.GetInt32(y));
                    a.Visible = true;
                }
                
            }
            Reader.Close();
        }
        public void savepic(int userid,string a)
        {
            Comm = new MySqlCommand("update user set imagepath= '" + a + "' where userid='" + userid + "'", Conn);
            Comm.ExecuteNonQuery();
        }
        public Boolean Friendjudge(int userid, string friend_id) {
            string a = "a", b = "b", c = "c";
            Comm = new MySqlCommand("select * from friends where userid='" + userid + "'", Conn);
            Reader = Comm.ExecuteReader();
            while (Reader.Read())
            {
                a = Reader.GetString(1);
                b = Reader.GetString(2);
                c = Reader.GetString(3);
            }
            Reader.Close();
            if (!a.Equals(friend_id) && !b.Equals(friend_id) && !c.Equals(friend_id))
            {
                MessageBox.Show("You havn't added this friend!"); return false;
            }
            else return true;

        }
        }
    }

