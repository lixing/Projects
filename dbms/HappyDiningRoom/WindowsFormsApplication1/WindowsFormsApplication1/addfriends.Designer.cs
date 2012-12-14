namespace WindowsFormsApplication1
{
    partial class addfriends
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.sqlSelectCommand1 = new System.Data.SqlClient.SqlCommand();
            this.sqlInsertCommand1 = new System.Data.SqlClient.SqlCommand();
            this.sqlUpdateCommand1 = new System.Data.SqlClient.SqlCommand();
            this.sqlDeleteCommand1 = new System.Data.SqlClient.SqlCommand();
            this.sqlDataAdapter1 = new System.Data.SqlClient.SqlDataAdapter();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxX1 = new DevComponents.DotNetBar.Controls.TextBoxX();
            this.crystalButton1 = new MyControls.CrystalButton();
            this.crystalButton2 = new MyControls.CrystalButton();
            this.crystalButton3 = new MyControls.CrystalButton();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.crystalButton4 = new MyControls.CrystalButton();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // sqlDataAdapter1
            // 
            this.sqlDataAdapter1.DeleteCommand = this.sqlDeleteCommand1;
            this.sqlDataAdapter1.InsertCommand = this.sqlInsertCommand1;
            this.sqlDataAdapter1.SelectCommand = this.sqlSelectCommand1;
            this.sqlDataAdapter1.UpdateCommand = this.sqlUpdateCommand1;
            // 
            // dataGridView1
            // 
            this.dataGridView1.BackgroundColor = System.Drawing.Color.White;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(174, 62);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(138, 172);
            this.dataGridView1.TabIndex = 3;
            this.dataGridView1.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Location = new System.Drawing.Point(37, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 6;
            this.label1.Text = "label1";
            // 
            // textBoxX1
            // 
            // 
            // 
            // 
            this.textBoxX1.Border.Class = "TextBoxBorder";
            this.textBoxX1.Location = new System.Drawing.Point(206, 35);
            this.textBoxX1.Name = "textBoxX1";
            this.textBoxX1.ReadOnly = true;
            this.textBoxX1.Size = new System.Drawing.Size(76, 21);
            this.textBoxX1.TabIndex = 7;
            this.textBoxX1.WatermarkColor = System.Drawing.Color.Black;
            this.textBoxX1.WatermarkText = "User List";
            // 
            // crystalButton1
            // 
            this.crystalButton1.BackColor = System.Drawing.Color.Red;
            this.crystalButton1.Font = new System.Drawing.Font("Arial Black", 12F, System.Drawing.FontStyle.Bold);
            this.crystalButton1.Location = new System.Drawing.Point(336, 62);
            this.crystalButton1.Name = "crystalButton1";
            this.crystalButton1.Size = new System.Drawing.Size(131, 53);
            this.crystalButton1.TabIndex = 8;
            this.crystalButton1.Text = "Add Friends";
            this.crystalButton1.UseVisualStyleBackColor = false;
            this.crystalButton1.Click += new System.EventHandler(this.crystalButton1_Click);
            // 
            // crystalButton2
            // 
            this.crystalButton2.BackColor = System.Drawing.Color.DarkTurquoise;
            this.crystalButton2.Font = new System.Drawing.Font("Arial Black", 12F, System.Drawing.FontStyle.Bold);
            this.crystalButton2.Location = new System.Drawing.Point(336, 121);
            this.crystalButton2.Name = "crystalButton2";
            this.crystalButton2.Size = new System.Drawing.Size(131, 55);
            this.crystalButton2.TabIndex = 9;
            this.crystalButton2.Text = "Visit Friends";
            this.crystalButton2.UseVisualStyleBackColor = true;
            this.crystalButton2.Click += new System.EventHandler(this.crystalButton2_Click);
            // 
            // crystalButton3
            // 
            this.crystalButton3.BackColor = System.Drawing.Color.DarkTurquoise;
            this.crystalButton3.Font = new System.Drawing.Font("Arial Black", 12F, System.Drawing.FontStyle.Bold);
            this.crystalButton3.Location = new System.Drawing.Point(233, 265);
            this.crystalButton3.Name = "crystalButton3";
            this.crystalButton3.Size = new System.Drawing.Size(134, 41);
            this.crystalButton3.TabIndex = 10;
            this.crystalButton3.Text = "Back";
            this.crystalButton3.UseVisualStyleBackColor = true;
            this.crystalButton3.Click += new System.EventHandler(this.crystalButton3_Click);
            // 
            // crystalButton4
            // 
            this.crystalButton4.BackColor = System.Drawing.Color.Yellow;
            this.crystalButton4.Font = new System.Drawing.Font("Arial Black", 12F, System.Drawing.FontStyle.Bold);
            this.crystalButton4.Location = new System.Drawing.Point(336, 182);
            this.crystalButton4.Name = "crystalButton4";
            this.crystalButton4.Size = new System.Drawing.Size(131, 51);
            this.crystalButton4.TabIndex = 11;
            this.crystalButton4.Text = "Hire Friends";
            this.crystalButton4.UseVisualStyleBackColor = false;
            this.crystalButton4.Click += new System.EventHandler(this.crystalButton4_Click);
            // 
            // addfriends
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::WindowsFormsApplication1.Properties.Resources.BJ;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(579, 318);
            this.Controls.Add(this.crystalButton4);
            this.Controls.Add(this.crystalButton3);
            this.Controls.Add(this.crystalButton2);
            this.Controls.Add(this.crystalButton1);
            this.Controls.Add(this.textBoxX1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridView1);
            this.Name = "addfriends";
            this.Text = "friends";
            this.Load += new System.EventHandler(this.friends_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Data.SqlClient.SqlCommand sqlSelectCommand1;
        private System.Data.SqlClient.SqlCommand sqlInsertCommand1;
        private System.Data.SqlClient.SqlCommand sqlUpdateCommand1;
        private System.Data.SqlClient.SqlCommand sqlDeleteCommand1;
        private System.Data.SqlClient.SqlDataAdapter sqlDataAdapter1;
        public System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Label label1;
        private DevComponents.DotNetBar.Controls.TextBoxX textBoxX1;
        private MyControls.CrystalButton crystalButton1;
        private MyControls.CrystalButton crystalButton2;
        private MyControls.CrystalButton crystalButton3;
        private System.Windows.Forms.Timer timer1;
        private MyControls.CrystalButton crystalButton4;


    }
}