   M S B A M L   `   `   `  ���� C  ?Controls, Version=2.2.1.0, Culture=neutral, PublicKeyToken=null?-clr-namespace:ESMP.Controls;assembly=ControlsESMP.Controls  N JMultiWeChatOpenTool, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null9!clr-namespace:MultiWeChatOpenToolMultiWeChatOpenTool $   MultiWeChatOpenTool.MainWindow   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     >Ctrl-clr-namespace:ESMP.Controls;assembly=Controls     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     3local!clr-namespace:MultiWeChatOpenTool     -     � 
ResizeMode$  NoResize=� � WindowStyle$
 None=� � WindowStartupLocation$ Manual=� � AllowsTransparency . 
�������
�������$��1q� � Title$ 微信多开助手��$	��300��$	��180�� � Icon$ 
PSLogo.ico��.���� .+��� $��
pslogo.ico��
 �� Top$ 5�� �� Left$ 10��$��20���� $��微信多开助手��$ 35��$ 5��!   ESMP.Controls.PictureButton   �� Right$ 25��	 � ToolTip$	 设置��$ 0��$��25��
   MouseMoveBackground
 �	#FFE5E5E5  -     Name$ CloseProgram��$	 关闭��$ 0��$ 0��$��25��
 �	#FFE74450.���� $��	Close.png���� -    ��Name$ WeChatProcesses��$	��150��$	��200��$ 14��$ 40��    ESMP.Controls.NormalButton  -     Name$ 
OpenWeChat��$��点我开启新微信��$ 14��$	 210��$	��150��$��30��
�������$��0q�"   ESMP.Controls.LinkTextButton     Text$ 设置��
�������   MouseMoveBrush
 ��  �$��12(�$ 20�� �� Bottom$ 30��  $ 关于��
�������
 ��  �$��12(�$ 65��$ 30��  $ 悬浮窗口��
�������
 ��  �$��12(�$	 110��$ 30���� $%��CopyRight © 2017 CailyPersonal��$��10(�$ 12��$ 5�����	#FFA3A3A3