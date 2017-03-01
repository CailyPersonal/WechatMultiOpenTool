using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Threading;
using System.Runtime.InteropServices;


namespace MultiWeChatOpenTool {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {

        private const string DefaultWeChatPath = @"C:\Program Files (x86)\Tencent\WeChat\WeChat.exe";

        private void AddWeChatInstanceToView(WeChatInstance Instance, bool Clear = false) {

            if (Clear) { WeChatProcesses.Children.Clear(); }

            WeChatProcesses.Children.Add(Instance);
        }

        public MainWindow() {

            InitializeComponent();

            this.Left = SystemParameters.WorkArea.Width - 200;
            this.Top = SystemParameters.WorkArea.Height - 320;

            ClearAllWeChatMutex();

            

        }

        [DllImport("WeChatJailbreak.dll", EntryPoint = "ClearWeChatMutex", CallingConvention = CallingConvention.Cdecl)]
        public static extern Boolean ClearWeChatMutex(UInt32 PID);

        /// <summary>
        /// 清除所有微信客户端中的互斥量
        /// </summary>
        /// <returns></returns>
        private bool ClearAllWeChatMutex() {
            Boolean Result = true;

            try {
                foreach (Process WeChatProcess in Process.GetProcessesByName("WeChat")) {
                    Result &= ClearWeChatMutex((UInt32)WeChatProcess.Id);
                }
            }
            catch(Exception e) {
                ESMP.Controls.IMessageBox.Show(e.Message, "检测到运行错误");
            }

            return true;
        }


        private void Window_MouseMove(object sender, MouseEventArgs e) {
            if(e.LeftButton == MouseButtonState.Pressed) {
                this.DragMove();
            }
        }


        private void OpenWeChat_Click(object sender, RoutedEventArgs e) {
            ClearAllWeChatMutex();
            try {
                Process WeChatProcess = Process.Start(DefaultWeChatPath);
                AddWeChatInstanceToView(new WeChatInstance(WeChatProcess));
            }
            catch(Exception ex) {
                ESMP.Controls.IMessageBox.Show(ex.Message, "检测到运行错误");
            }
        }

        private void Close_Click(object sender, RoutedEventArgs e) {
            Application.Current.Shutdown();
        }
    }
}
