using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace TCS.Installer
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
            this.Size = new Size(494, 358);
        }

 

        private void btnSelectPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.SelectedPath = txtLocPath.Text;
            if (fbd.ShowDialog(this) == DialogResult.OK)
            {
                txtLocPath.Text = fbd.SelectedPath;
            }
            fbd.Dispose();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            this.Icon = Properties.Resources.ico;
           
            if (!System.IO.Directory.Exists(txtLocPath.Text) || txtLocPath.Text.Trim() == "")
            {
                txtLocPath.Text = Application.StartupPath;
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        FTP ftp = null;
        private void btnDo_Click(object sender, EventArgs e)
        {
            try
            {
                bool result = true;
                btnUpLoadBoot.Enabled = false;
                ShowInfo("正在准备...");
                ftp = new FTP(cbxIP.Text, txUser.Text, txtPassword.Text);
                ShowInfo(string.Format("准备ftp,参数： ftp://{0}:{1}@{2}/{3}   本地{4}", txUser.Text, txtPassword.Text, cbxIP.Text, txtRemotPath.Text, txtLocPath.Text));
                if (txtRemotPath.Text.StartsWith("/") || txtRemotPath.Text.StartsWith("\\"))
                {
                    ftp.RootPath = txtRemotPath.Text.Remove(0, 1);
                }
                else
                {
                    ftp.RootPath = ftp.RootPath;
                }
                ShowInfo("正在上载启动文件...");

                if (result)
                {
                    result = Upload("etc/rc.local");
                }
                if (result)
                {
                    result = Upload("etc/rc.local.base");
                }
                if (result)
                {
                    ShowInfo("请重新启动车道...");
                }
                btnUploadFiles.Enabled = true;
                btnNext3_Click(null, null);
            }
            catch (Exception ex)
            {
                btnUpLoadBoot.Enabled = true;
                ShowInfo(ex.Message);
            }

        }
        private bool Upload(string filename)
        {
            return ftp.UploadFile(filename, System.IO.File.ReadAllBytes(GetFileName(filename.Replace("/", "\\"))));
        }
        private bool Upload(string filename, string  context)
        {
            return ftp.UploadFile(filename.Replace("\\", "//"), System.Text.Encoding.Default.GetBytes(context));
        }
        private string GetFileName(string path)
        {
            return txtLocPath.Text + "\\Package\\" + path;
        }
        void ShowInfo(string txt)
        {
            if (txt != null)
            {
                lblInfo.Text = txt;
                txtNow.AppendText ( txt+System.Environment.NewLine) ;
                txtNow.ScrollToCaret();
                Application.DoEvents();
                System.IO.File.AppendAllText(GetFileName("install.log"),DateTime.Now.ToString()+"::::"+ txt+Environment.NewLine , Encoding.UTF8);
            }

        }

        private void btnUploadFiles_Click(object sender, EventArgs e)
        {
            try
            {
 
                ShowInfo("正在检查目录...");
                CheckPath(GetFileName("Data"));
                ShowInfo("目录检查完成...");
                UploadDirs(GetFileName("Data"));
                ShowInfo("上传完毕，请重启车道。");

            }
            catch (Exception ex)
            {
 
                ShowInfo("上传过程中出现错误，请重新上传!错误内容:" + ex.Message);
            }
        }
        public void CheckPath(string dirname)
        {
            try
            {
                ShowInfo("开始检查目录:" + dirname);
                string[] dirloc = System.IO.Directory.GetDirectories(dirname);
                string[] dirrmt = ftp.ListDir(dirname.Remove(0, GetFileName("").Length));
                string rootpath = dirname.Remove(0, GetFileName("").Length);
                foreach (var item in dirloc)
                {
                    string path = item.Remove(0, dirname.Length + 1);
                    int i = Array.BinarySearch(dirrmt, path);
                    if (i < 0)
                    {
                        ShowInfo("正在创建远程目录:" + path);
                        ftp.MkDir(rootpath + "//" + path);
                    }
                    else
                    {
                        CheckPath(dirname + "\\" + path);
                    }
                }
                ShowInfo("完成检查目录" + dirname);
            }
            catch (Exception ex)
            {
                ShowInfo("检查目录时遇到一场:" + ex.Message);
            }
        }
        public void UploadDirs(string dirname)
        {
            try
            {
                string[] dirloc = System.IO.Directory.GetDirectories(dirname);
                string[] dirrmt = ftp.ListDir(dirname.Remove(0, GetFileName("").Length));
                string rootpath = dirname.Remove(0, GetFileName("").Length);
                foreach (var item in dirloc)
                {
                    Application.DoEvents();
                    string path = item.Remove(0, dirname.Length + 1);
                    if (path == ".svn" || path == "_svn")
                    {
                        continue;
                    }
                    bool i = false ; ;
                    foreach (var itemxxx in dirrmt)
                    {
                        i = itemxxx == path;
                        if (i) break;
                    }
                    if (i ==false )
                    {
                        ftp.MkDir(rootpath + "//" + path);
                    }
                    else
                    {
                        UploadDirs(dirname + "\\" + path);
                    }
                }
                Application.DoEvents();
                string[] locfile = System.IO.Directory.GetFiles(dirname);
                string fileroot = GetFileName("");
                foreach (var ifile in locfile)
                {
                    string tmpf = ifile.Remove(0, GetFileName("").Length);
                    Application.DoEvents();
                    if (tmpf == ConfigINI)
                    {
                        changelane();
                    }
                    else
                    {
                        bool b = Upload(tmpf);
                        ShowInfo("文件【" + tmpf + "】上传" + (b ? "成功!" : "失败"));
                    }
                    Application.DoEvents();
                    System.Threading.Thread.Sleep(5);
                }
                ShowInfo("目录" + rootpath + "上传完毕!");
            }
            catch (Exception ex)
            {
                ShowInfo(ex.Message);
            }
        }

        private void btnNetx1_Click(object sender, EventArgs e)
        {
            ShowPanel(2);
        }
        const string ConfigINI = @"Data\EMRCV3\CONFIG\Config.ini";
        void changelane()
        {
            
            string f = GetFileName(ConfigINI);
            if (System.IO.File.Exists(f))
            {
                ShowInfo("上传配置文件(车道号为:" + cbxLaneNo.Text.Trim() + " 车道类型" + (rbUp.Checked ? "U" : "D") + ")" + f);
                string context = System.IO.File.ReadAllText(f, Encoding.Default);
                context = context.Replace("{LANENO}", cbxLaneNo.Text.Trim());
                context = context.Replace("{LANETYPE}", rbUp.Checked ? "U" : "D");
                bool ok = Upload(ConfigINI, context);
                ShowInfo("文件【" + ConfigINI + "】上传" + (ok ? "成功!" : "失败"));
            }
        }

        private void btnNext2_Click(object sender, EventArgs e)
        {
            ShowPanel(3);
        }
        private void btnNext3_Click(object sender, EventArgs e)
        {
            ShowPanel(4);
        }
        void ShowPanel(int step )
        {
            for (int i = 0; i <= 4; i++)
            {
                ShowPanl(i, i == step); 
            }
        }
        private void ShowPanl(int step,bool ctlvisible)
        {
             string key="step"+step.ToString();
             Control[] ctls = this.Controls.Find(key,true );
             if (ctls.Length >= 1)
             {
                 ctls[0].Visible = ctlvisible;
                 ctls[0].Location = step1.Location;
                 ctls[0].Size  = step1.Size ;
             }
        }

        private void step2_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
