using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Timers;
using System.Diagnostics;
using System.Windows.Media.Imaging;
using System.Runtime.InteropServices;

namespace MultiWeChatOpenTool {
    class WeChatInstance : ESMP.Controls.TextButtonWithIcon {
        private int _WeChatProcessId;
        private Timer _BackgroudTimer;
        private bool Online = false;
        private string WeChatId;

        public WeChatInstance(Process WeChatProcess) {
            _WeChatProcessId = WeChatProcess.Id;
            _BackgroudTimer = new Timer(500);
            _BackgroudTimer.Elapsed += UpdateWeChatRunStatus;
            _BackgroudTimer.Enabled = true;
            _BackgroudTimer.Start();

            BitmapImage WeChatIcon = new BitmapImage(new Uri("/MultiWeChatOpenTool;component/wechat.ico", UriKind.Relative));

            DefaultIcon = WeChatIcon;
            MouseMoveIcon = WeChatIcon;

            Content = "登录...";
            Margin = new Thickness(0, 5, 0, 5);
        }

        [DllImport("User32.Dll")]
        private static extern void GetClassName(IntPtr hwnd,[Out] StringBuilder s, int nMaxCount);

        [DllImport("WeChatJailbreak.dll", CallingConvention = CallingConvention.Cdecl,CharSet = CharSet.Unicode)]
        private static extern bool GetWeChatID(UInt32 PID);

        private void UpdateWeChatRunStatus(object sender, ElapsedEventArgs e) {
            try {

                StringBuilder name = new StringBuilder();
                GetClassName(Process.GetProcessById(_WeChatProcessId).MainWindowHandle,name,256);

                Dispatcher.Invoke(new Action(delegate {
                    switch (name.ToString()) {
                        case "WeChatLoginWndForPC":
                            Content = "登录...";
                            Online = false;
                            WeChatId = "";
                            break;
                        case "WeChatMainWndForPC":
                        case "CMenuWnd":
                            Online = true;

                            // string is transfered by clipboard
                            if(string.IsNullOrEmpty(WeChatId) && true == GetWeChatID((UInt32)_WeChatProcessId)) {
                                IDataObject iData = Clipboard.GetDataObject();

                                // A standard string is like: \Sessions\1\BaseNamedObjects\xxx_WeChat_Win_User_Identity_Mutex_Name    xxx is id of WeChat
                                string full = (string)iData.GetData(DataFormats.UnicodeText);
                                if (full.Contains("_WeChat_Win_User_Identity_Mutex_Name")) {
                                    WeChatId = full.Substring(29, full.Length - 65);
                                }
                               
                            }
                            Content = $"{WeChatId}-在线";
                            break;
                        case "":
                            Content = Online ? "在线" : "登录...";
                            break;
                        //default:
                        //    MessageBox.Show(name.ToString());
                        //    break;
                    }
                }));
            }
            catch (Exception ex){
                Dispatcher.Invoke(new Action(delegate {
                    Content = "客户端已关闭";
                    _BackgroudTimer.Stop();
                    //MessageBox.Show(ex.ToString(), "检测运行状态错误");
                    return;
                }));
            }
        }
    }
}
