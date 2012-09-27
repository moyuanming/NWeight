using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.IO;

namespace TCS.Installer
{
    public class FTP
    {
        public FTP()
        {
        }

        public FTP(string ipaddress, string user, string password)
        {
            IPAddress = ipaddress;
            User = user;
            Password = password;
        }
        public FTP(string ipaddress, string user, string password, string rootpath)
        {
            IPAddress = ipaddress;
            User = user;
            Password = password;
            RootPath = rootpath;
        }
        /// <summary>
        /// IP地址
        /// </summary>
        public string IPAddress { get; set; }
        /// <summary>
        /// 用户名
        /// </summary>
        public string User { get; set; }
        /// <summary>
        /// 密码
        /// </summary>
        public string Password { get; set; }
        /// <summary>
        /// 跟路径
        /// </summary>
        public string RootPath { get; set; }
        /// <summary>
        /// 删除文件
        /// </summary>
        /// <param name="filename">指定文件名</param>
        /// <returns></returns>
        public bool DelFile(string filename)
        {
            bool result = false;
            FtpWebResponse fwr = null;
            try
            {
                FtpWebRequest fwp = (FtpWebRequest)FtpWebRequest.Create(string.Format("ftp://{0}:{1}@{2}/{3}/{4}", User, Password, IPAddress, RootPath, filename));
                fwp.Method = WebRequestMethods.Ftp.DeleteFile;
                fwr = (FtpWebResponse)fwp.GetResponse();
                result = fwr.StatusDescription.StartsWith(((int)FtpStatusCode.FileActionOK).ToString());

            }
            catch (Exception) { }
            finally
            {
                if (fwr != null)
                {
                    fwr.Close();
                }
            }
            return result;

        }
        /// <summary>
        /// 删除目录
        /// </summary>
        /// <param name="dirname">要删除的目录名</param>
        /// <returns></returns>
        public bool DelDir(string dirname)
        {
            bool result = false;
            FtpWebResponse fwr = null;
            try
            {
                FtpWebRequest fwp = (FtpWebRequest)FtpWebRequest.Create(string.Format("ftp://{0}:{1}@{2}/{3}/{4}", User, Password, IPAddress, RootPath, dirname));
                fwp.Method = WebRequestMethods.Ftp.RemoveDirectory;
                fwr = (FtpWebResponse)fwp.GetResponse();
                string fsc = Enum.GetName(typeof(FtpStatusCode), 250);
                result = fwr.StatusDescription.StartsWith(((int)FtpStatusCode.FileActionOK).ToString());
            }
            catch (Exception) { }
            finally
            {
                if (fwr != null)
                {
                    fwr.Close();
                }
            }
            return result;
        }
        public bool MkDir(string dirname)
        {
            bool result = false;
            FtpWebResponse fwr = null;
            try
            {
                FtpWebRequest fwp = (FtpWebRequest)FtpWebRequest.Create(string.Format("ftp://{0}:{1}@{2}/{3}/{4}", User, Password, IPAddress, RootPath, dirname ));
                fwp.Method = WebRequestMethods.Ftp.MakeDirectory ;
                fwr = (FtpWebResponse)fwp.GetResponse();
                string fsc = Enum.GetName(typeof(FtpStatusCode), 257);
                result = fwr.StatusDescription.StartsWith(((int)FtpStatusCode.PathnameCreated ).ToString());

            }
            catch (Exception) { }
            finally
            {
                if (fwr != null)
                {
                    fwr.Close();
                }
            }
            return result;

        }

        /// <summary>
        /// 列出目录
        /// </summary>
        /// <param name="dirname">指定目录名</param>
        /// <returns></returns>
        public string[] ListDir(string dirname)
        {
            string[] files = null;
            string[] dirs = null;
            List(dirname, out dirs, out files);
            return dirs;
        }
        /// <summary>
        /// 列出文件
        /// </summary>
        /// <param name="dirname"></param>
        /// <returns></returns>
        public string[] ListFiles(string dirname)
        {
            string[] files = null;
            string[] dirs = null;
            List(dirname, out dirs, out files);
            return files;
        }
        public void List(string dirname, out string[] dirs, out string[] files)
        {
            Stream responseStream = null;
            StreamReader readStream = null;
            FtpWebResponse response = null;
            dirs = null;
            files = null;
            try
            {
                FtpWebRequest fwp = (FtpWebRequest)FtpWebRequest.Create(string.Format("ftp://{0}:{1}@{2}/{3}/{4}", User, Password, IPAddress, RootPath, dirname));
                fwp.Method = WebRequestMethods.Ftp.ListDirectoryDetails;
                response = (FtpWebResponse)fwp.GetResponse();
                string fsc = Enum.GetName(typeof(FtpStatusCode), 150);
                if (response.StatusDescription.StartsWith(((int)FtpStatusCode.OpeningData).ToString()))
                {
                    responseStream = response.GetResponseStream();
                    readStream = new StreamReader(responseStream, System.Text.Encoding.UTF8);
                    if (readStream != null)
                    {
                        string tmp = readStream.ReadToEnd();
                        string[] tmpary = tmp.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
                        string xxx = "";
                        string xxx2 = "";
                        foreach (var item in tmpary)
                        {
                            if (item.IndexOf(':') >= 0)
                            {
                                if (item.StartsWith("d"))
                                {
                                    xxx += "\r\n" + item.Substring(item.IndexOf(' ', item.IndexOf(':'))).Trim();
                                }
                                else if (item.StartsWith("-"))
                                {
                                    xxx2 += "\r\n" + item.Substring(item.IndexOf(' ', item.IndexOf(':'))).Trim();
                                }
                            }
                        }
                        dirs = xxx.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
                        files = xxx2.Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
                    }
                }
            }
            finally
            {
                if (readStream != null)
                {
                    readStream.Close();
                }
                if (response != null)
                {
                    response.Close();
                }
            }
        }
        public byte[] DownloadFile(string filename)
        {
            Stream responseStream = null;
            StreamReader readStream = null;
            FtpWebResponse response = null;
            byte[] result = null;
            try
            {
                FtpWebRequest fwp = (FtpWebRequest)FtpWebRequest.Create(string.Format("ftp://{0}:{1}@{2}/{3}/{4}", User, Password, IPAddress, RootPath, filename));
                fwp.Method = WebRequestMethods.Ftp.DownloadFile;
                response = (FtpWebResponse)fwp.GetResponse();
                string fsc = Enum.GetName(typeof(FtpStatusCode), 150);
                if (response.StatusDescription.StartsWith(((int)FtpStatusCode.OpeningData).ToString()))
                {
                    responseStream = response.GetResponseStream();
                    readStream = new StreamReader(responseStream, Encoding.ASCII);
                    if (readStream != null)
                    {
                        char[] bytes = new char[1024];
                        MemoryStream ms = new MemoryStream();
                        StreamWriter sw = new StreamWriter(ms);
                        int i;
                        while ((i = readStream.Read(bytes, 0, bytes.Length)) != 0)
                        {
                            sw.Write(bytes, 0, i);

                        }
                        sw.Close();
                        result = ms.ToArray().Clone() as byte[];
                        ms.Close();

                    }
                }
            }
            finally
            {
                if (readStream != null)
                {
                    readStream.Close();
                }
                if (response != null)
                {
                    response.Close();
                }
            }
            return result;
        }
        public bool UploadFile(string filename, byte[] buffer)
        {
            Stream requestStream = null;
            StreamWriter writeStream = null;
            FtpWebResponse response = null;
            bool result = false;
            try
            {
                FtpWebRequest fwp = (FtpWebRequest)FtpWebRequest.Create(string.Format("ftp://{0}:{1}@{2}/{3}/{4}", User, Password, IPAddress, RootPath, filename));
                fwp.Method = WebRequestMethods.Ftp.UploadFile;
                response = (FtpWebResponse)fwp.GetResponse();
                requestStream = fwp.GetRequestStream();
                requestStream.Write(buffer, 0, buffer.Length);
                requestStream.Close();
                response = (FtpWebResponse)fwp.GetResponse();
                string fsc = Enum.GetName(typeof(FtpStatusCode), 226);
                if (response.StatusDescription.StartsWith(((int)FtpStatusCode.ClosingData).ToString()))
                {

                    result = true;
                }
            }
            finally
            {
                if (writeStream != null)
                {
                    writeStream.Close();
                }
                if (response != null)
                {
                    response.Close();
                }
            }
            return result;
        }
    }
}
