   M S B A M L   `   `   `  ����C  ?Controls, Version=2.2.1.0, Culture=neutral, PublicKeyToken=null?-clr-namespace:ESMP.Controls;assembly=ControlsESMP.Controls  5   	   N JMultiWeChatOpenTool, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null9!clr-namespace:MultiWeChatOpenToolMultiWeChatOpenTool 5   	   $   MultiWeChatOpenTool.MainWindow   5   	   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   >Ctrl-clr-namespace:ESMP.Controls;assembly=Controls     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   3local!clr-namespace:MultiWeChatOpenTool     5   	   -   5          � 
ResizeMode$  NoResize=�5       � WindowStyle$
 None=�60    � WindowStartupLocation$ Manual=�6C    � AllowsTransparency . 
�������
�������$��1q�5	   S    � Title$ 微信多开助手��5
   	   $	��300��6   $	��180��6%    � Icon$ 
PSLogo.ico��61   .��5      �� .+�5   
   �� $��
pslogo.ico��6   
 �� Top$ 5��6$    �� Left$ 10��63   $��20��6D   �� 5   
   $��微信多开助手��6   $ 35��6"   $ 5��63   !   ESMP.Controls.PictureButton  5   
    �� Right$ 25��6   	 � ToolTip$	 设置��6/   $ 0��6<   $��25��6K   
   MouseMoveBackground
 �	#FFE5E5E56W     5   
   -   5          Name$ CloseProgram��5      $	 关闭��6G   $ 0��6T   $ 0��6e   $��25��6t   
 �	#FFE74450.��5      �� $��	Close.png��6   5      �� 5   
   -   5         ��Name$ WeChatProcesses��5      $	��150��6.   $	��200��6:   $ 14��6G   $ 40��6X   5          ESMP.Controls.NormalButton  5   
   -   5          Name$ 
OpenWeChat��5      $��点我开启新微信��60   $ 14��6B   $	 210��6S   $	��150��6d   $��30��6p   
�������$��0q�6�   6�   "   ESMP.Controls.LinkTextButton  5   
      Text$ 设置��6   
�������   MouseMoveBrush
 ��  �$��12(�6P   $ 20��6^    �� Bottom$ 30��6o     5   
   $ 关于��6   
�������
 ��  �$��12(�6P   $ 65��6^   $ 30��6o     5   
   $ 悬浮窗口��6   
�������
 ��  �$��12(�6R   $	 110��6`   $ 30��6r   �� 5   
   $%��CopyRight © 2017 CailyPersonal��6   $��10(�6:   $ 12��6H   $ 5��6Y   ���	#FFA3A3A36k   5       5"      