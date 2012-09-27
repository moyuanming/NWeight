namespace TCS.Installer
{
    partial class frmMain
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
            this.btnUpLoadBoot = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.cbxIP = new System.Windows.Forms.ComboBox();
            this.txUser = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtPassword = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtLocPath = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.txtRemotPath = new System.Windows.Forms.TextBox();
            this.btnSelectPath = new System.Windows.Forms.Button();
            this.btnUploadFiles = new System.Windows.Forms.Button();
            this.btnNext2 = new System.Windows.Forms.Button();
            this.label12 = new System.Windows.Forms.Label();
            this.btnNetx1 = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.lblInfo = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.label11 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.step1 = new System.Windows.Forms.Panel();
            this.step2 = new System.Windows.Forms.Panel();
            this.label13 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.rbDown = new System.Windows.Forms.RadioButton();
            this.rbUp = new System.Windows.Forms.RadioButton();
            this.cbxLaneNo = new System.Windows.Forms.ComboBox();
            this.step3 = new System.Windows.Forms.Panel();
            this.step4 = new System.Windows.Forms.Panel();
            this.txtNow = new System.Windows.Forms.TextBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.step1.SuspendLayout();
            this.step2.SuspendLayout();
            this.step3.SuspendLayout();
            this.step4.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnUpLoadBoot
            // 
            this.btnUpLoadBoot.Location = new System.Drawing.Point(229, 206);
            this.btnUpLoadBoot.Name = "btnUpLoadBoot";
            this.btnUpLoadBoot.Size = new System.Drawing.Size(90, 30);
            this.btnUpLoadBoot.TabIndex = 1;
            this.btnUpLoadBoot.Text = "准备";
            this.btnUpLoadBoot.UseVisualStyleBackColor = true;
            this.btnUpLoadBoot.Click += new System.EventHandler(this.btnDo_Click);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(383, 283);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(90, 30);
            this.btnClose.TabIndex = 2;
            this.btnClose.Text = "关闭";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "选择车道IP地址:";
            // 
            // cbxIP
            // 
            this.cbxIP.FormattingEnabled = true;
            this.cbxIP.Items.AddRange(new object[] {
            "192.168.1.188",
            "192.168.1.111"});
            this.cbxIP.Location = new System.Drawing.Point(104, 9);
            this.cbxIP.Name = "cbxIP";
            this.cbxIP.Size = new System.Drawing.Size(330, 20);
            this.cbxIP.TabIndex = 5;
            this.cbxIP.Text = "192.168.1.188";
            // 
            // txUser
            // 
            this.txUser.Location = new System.Drawing.Point(104, 58);
            this.txUser.Name = "txUser";
            this.txUser.Size = new System.Drawing.Size(131, 21);
            this.txUser.TabIndex = 6;
            this.txUser.Text = "root";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(48, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "用户名:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(264, 61);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 9;
            this.label3.Text = "密码:";
            // 
            // txtPassword
            // 
            this.txtPassword.Location = new System.Drawing.Point(305, 58);
            this.txtPassword.Name = "txtPassword";
            this.txtPassword.Size = new System.Drawing.Size(129, 21);
            this.txtPassword.TabIndex = 8;
            this.txtPassword.Text = "kissme";
            this.txtPassword.UseSystemPasswordChar = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(24, 103);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(71, 12);
            this.label4.TabIndex = 11;
            this.label4.Text = "本地根路径:";
            // 
            // txtLocPath
            // 
            this.txtLocPath.Location = new System.Drawing.Point(104, 100);
            this.txtLocPath.Name = "txtLocPath";
            this.txtLocPath.Size = new System.Drawing.Size(280, 21);
            this.txtLocPath.TabIndex = 10;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(24, 143);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 12);
            this.label5.TabIndex = 13;
            this.label5.Text = "远程根路径:";
            // 
            // txtRemotPath
            // 
            this.txtRemotPath.Location = new System.Drawing.Point(106, 140);
            this.txtRemotPath.Name = "txtRemotPath";
            this.txtRemotPath.Size = new System.Drawing.Size(328, 21);
            this.txtRemotPath.TabIndex = 12;
            this.txtRemotPath.Text = "/";
            // 
            // btnSelectPath
            // 
            this.btnSelectPath.Location = new System.Drawing.Point(391, 98);
            this.btnSelectPath.Name = "btnSelectPath";
            this.btnSelectPath.Size = new System.Drawing.Size(43, 23);
            this.btnSelectPath.TabIndex = 14;
            this.btnSelectPath.Text = "浏览";
            this.btnSelectPath.UseVisualStyleBackColor = true;
            this.btnSelectPath.Click += new System.EventHandler(this.btnSelectPath_Click);
            // 
            // btnUploadFiles
            // 
            this.btnUploadFiles.Enabled = false;
            this.btnUploadFiles.Location = new System.Drawing.Point(229, 206);
            this.btnUploadFiles.Name = "btnUploadFiles";
            this.btnUploadFiles.Size = new System.Drawing.Size(90, 30);
            this.btnUploadFiles.TabIndex = 16;
            this.btnUploadFiles.Text = "开始";
            this.btnUploadFiles.UseVisualStyleBackColor = true;
            this.btnUploadFiles.Click += new System.EventHandler(this.btnUploadFiles_Click);
            // 
            // btnNext2
            // 
            this.btnNext2.Location = new System.Drawing.Point(229, 206);
            this.btnNext2.Name = "btnNext2";
            this.btnNext2.Size = new System.Drawing.Size(90, 30);
            this.btnNext2.TabIndex = 15;
            this.btnNext2.Text = "下一步";
            this.btnNext2.UseVisualStyleBackColor = true;
            this.btnNext2.Click += new System.EventHandler(this.btnNext2_Click);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label12.ForeColor = System.Drawing.Color.Black;
            this.label12.Location = new System.Drawing.Point(3, 44);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(365, 48);
            this.label12.TabIndex = 17;
            this.label12.Text = "此操作将更新车道软件，这会影响到车道收费的整个过程。\r\n更新前必须仔细阅读注意事项，避免出现意外。\r\n继续操作将可能导致严重的后果。除非你明确的知道自己在做什么！" +
                "\r\n\r\n";
            // 
            // btnNetx1
            // 
            this.btnNetx1.Location = new System.Drawing.Point(229, 206);
            this.btnNetx1.Name = "btnNetx1";
            this.btnNetx1.Size = new System.Drawing.Size(90, 30);
            this.btnNetx1.TabIndex = 16;
            this.btnNetx1.Text = "下一步";
            this.btnNetx1.UseVisualStyleBackColor = true;
            this.btnNetx1.Click += new System.EventHandler(this.btnNetx1_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 17);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(269, 12);
            this.label6.TabIndex = 0;
            this.label6.Text = "欢迎使用车道软件安装程序，点击下一步进行安装";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(77, 206);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(90, 30);
            this.button1.TabIndex = 16;
            this.button1.Text = "上一步";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.btnNetx1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(77, 206);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(90, 30);
            this.button2.TabIndex = 17;
            this.button2.Text = "上一步";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.btnNext2_Click);
            // 
            // label8
            // 
            this.label8.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.ForeColor = System.Drawing.Color.Black;
            this.label8.Location = new System.Drawing.Point(2, 77);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(365, 36);
            this.label8.TabIndex = 3;
            this.label8.Text = "点击准备后将转换到下一步操作后请重启车道。";
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(3, 16);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(416, 37);
            this.label7.TabIndex = 2;
            this.label7.Text = "请确保车道机的网络是通畅的，然后点击准备上传引导文件，请确保车道机内etc/rc.local具备可执行权限。";
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(3, 5);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(345, 19);
            this.label10.TabIndex = 17;
            this.label10.Text = "此步陬将所有文件上传至车道。请确保网络通畅。";
            // 
            // lblInfo
            // 
            this.lblInfo.Location = new System.Drawing.Point(3, 24);
            this.lblInfo.Name = "lblInfo";
            this.lblInfo.Size = new System.Drawing.Size(467, 29);
            this.lblInfo.TabIndex = 16;
            this.lblInfo.Text = "在点击【开始】按钮前重新启动车道且只能重启一次。";
            // 
            // panel3
            // 
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel3.Location = new System.Drawing.Point(-1, 266);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(644, 4);
            this.panel3.TabIndex = 20;
            // 
            // panel4
            // 
            this.panel4.BackColor = System.Drawing.Color.White;
            this.panel4.Controls.Add(this.label11);
            this.panel4.Controls.Add(this.pictureBox1);
            this.panel4.Location = new System.Drawing.Point(-1, -1);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(624, 67);
            this.panel4.TabIndex = 21;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(12, 25);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(119, 12);
            this.label11.TabIndex = 1;
            this.label11.Text = "欢迎使用TCS安装程序";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::TCS.Installer.Properties.Resources.setup;
            this.pictureBox1.Location = new System.Drawing.Point(405, 4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(82, 60);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // step1
            // 
            this.step1.Controls.Add(this.label12);
            this.step1.Controls.Add(this.label6);
            this.step1.Controls.Add(this.btnNetx1);
            this.step1.Location = new System.Drawing.Point(12, 76);
            this.step1.Name = "step1";
            this.step1.Size = new System.Drawing.Size(481, 260);
            this.step1.TabIndex = 22;
            // 
            // step2
            // 
            this.step2.Controls.Add(this.label13);
            this.step2.Controls.Add(this.label9);
            this.step2.Controls.Add(this.rbDown);
            this.step2.Controls.Add(this.rbUp);
            this.step2.Controls.Add(this.cbxLaneNo);
            this.step2.Controls.Add(this.button1);
            this.step2.Controls.Add(this.label1);
            this.step2.Controls.Add(this.btnNext2);
            this.step2.Controls.Add(this.label5);
            this.step2.Controls.Add(this.cbxIP);
            this.step2.Controls.Add(this.txtPassword);
            this.step2.Controls.Add(this.txtLocPath);
            this.step2.Controls.Add(this.label2);
            this.step2.Controls.Add(this.txtRemotPath);
            this.step2.Controls.Add(this.label4);
            this.step2.Controls.Add(this.btnSelectPath);
            this.step2.Controls.Add(this.txUser);
            this.step2.Controls.Add(this.label3);
            this.step2.Location = new System.Drawing.Point(513, 345);
            this.step2.Name = "step2";
            this.step2.Size = new System.Drawing.Size(487, 238);
            this.step2.TabIndex = 23;
            this.step2.Paint += new System.Windows.Forms.PaintEventHandler(this.step2_Paint);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(240, 35);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(59, 12);
            this.label13.TabIndex = 21;
            this.label13.Text = "车道类型:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(48, 36);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 12);
            this.label9.TabIndex = 20;
            this.label9.Text = "车道号:";
            // 
            // rbDown
            // 
            this.rbDown.AutoSize = true;
            this.rbDown.Location = new System.Drawing.Point(387, 33);
            this.rbDown.Name = "rbDown";
            this.rbDown.Size = new System.Drawing.Size(47, 16);
            this.rbDown.TabIndex = 19;
            this.rbDown.TabStop = true;
            this.rbDown.Text = "下行";
            this.rbDown.UseVisualStyleBackColor = true;
            // 
            // rbUp
            // 
            this.rbUp.AutoSize = true;
            this.rbUp.Checked = true;
            this.rbUp.Location = new System.Drawing.Point(305, 33);
            this.rbUp.Name = "rbUp";
            this.rbUp.Size = new System.Drawing.Size(47, 16);
            this.rbUp.TabIndex = 18;
            this.rbUp.TabStop = true;
            this.rbUp.Text = "上行";
            this.rbUp.UseVisualStyleBackColor = true;
            // 
            // cbxLaneNo
            // 
            this.cbxLaneNo.FormattingEnabled = true;
            this.cbxLaneNo.Items.AddRange(new object[] {
            "X01",
            "X02",
            "X03",
            "X04",
            "X05",
            "X06",
            "X07",
            "X08",
            "X09",
            "X10",
            "E01",
            "E02",
            "E03",
            "E04",
            "E05",
            "E06",
            "E07",
            "E08",
            "E09",
            "E10"});
            this.cbxLaneNo.Location = new System.Drawing.Point(104, 33);
            this.cbxLaneNo.Name = "cbxLaneNo";
            this.cbxLaneNo.Size = new System.Drawing.Size(131, 20);
            this.cbxLaneNo.TabIndex = 17;
            this.cbxLaneNo.Text = "X01";
            // 
            // step3
            // 
            this.step3.Controls.Add(this.button2);
            this.step3.Controls.Add(this.label7);
            this.step3.Controls.Add(this.label8);
            this.step3.Controls.Add(this.btnUpLoadBoot);
            this.step3.Location = new System.Drawing.Point(32, 345);
            this.step3.Name = "step3";
            this.step3.Size = new System.Drawing.Size(461, 235);
            this.step3.TabIndex = 24;
            // 
            // step4
            // 
            this.step4.Controls.Add(this.txtNow);
            this.step4.Controls.Add(this.label10);
            this.step4.Controls.Add(this.lblInfo);
            this.step4.Controls.Add(this.btnUploadFiles);
            this.step4.Location = new System.Drawing.Point(508, 76);
            this.step4.Name = "step4";
            this.step4.Size = new System.Drawing.Size(492, 258);
            this.step4.TabIndex = 25;
            // 
            // txtNow
            // 
            this.txtNow.Location = new System.Drawing.Point(5, 56);
            this.txtNow.Multiline = true;
            this.txtNow.Name = "txtNow";
            this.txtNow.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtNow.Size = new System.Drawing.Size(465, 126);
            this.txtNow.TabIndex = 18;
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel2.Location = new System.Drawing.Point(-1, 66);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(627, 4);
            this.panel2.TabIndex = 26;
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1113, 643);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.step3);
            this.Controls.Add(this.step2);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.step4);
            this.Controls.Add(this.step1);
            this.Controls.Add(this.panel4);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "车道软件安装(TCS)";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.panel4.ResumeLayout(false);
            this.panel4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.step1.ResumeLayout(false);
            this.step1.PerformLayout();
            this.step2.ResumeLayout(false);
            this.step2.PerformLayout();
            this.step3.ResumeLayout(false);
            this.step4.ResumeLayout(false);
            this.step4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnUpLoadBoot;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbxIP;
        private System.Windows.Forms.TextBox txUser;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtPassword;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtLocPath;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtRemotPath;
        private System.Windows.Forms.Button btnSelectPath;
        private System.Windows.Forms.Button btnUploadFiles;
        private System.Windows.Forms.Button btnNext2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btnNetx1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label lblInfo;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Panel step1;
        private System.Windows.Forms.Panel step2;
        private System.Windows.Forms.Panel step3;
        private System.Windows.Forms.Panel step4;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox txtNow;
        private System.Windows.Forms.ComboBox cbxLaneNo;
        private System.Windows.Forms.RadioButton rbDown;
        private System.Windows.Forms.RadioButton rbUp;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label9;

    }
}

