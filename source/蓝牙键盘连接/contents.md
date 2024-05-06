# Ubuntu连接蓝牙键盘

我在升级完ubuntu之后发现无论是通过系统蓝牙还是通过blueman连接罗技MX keys蓝牙键盘都会出现断开连接的情况，而且频率非常高。我开始以为是键盘问题，故更换为另一款k580的蓝牙键盘，尝试开始连接，这次更夸张地直接都配对不了。

在网上看到大神的建议[求助，罗技k380蓝牙键盘在ubuntucinnamon20.04.6上无法使用 - Ubuntu中文论坛](https://forum.ubuntu.org.cn/viewtopic.php?p=3236056)，成功地用`bluetoothctl`连接上了我的蓝牙键盘。

具体来说步骤是：

```bash
bluetoothctl
# 接下来你进入了bluetoothctl
agent on
scan on
# 这个时候你应该能扫描到你的蓝牙键盘
# 配对设备
pair D5:D5:62:51:82:EF
# 这个时候会提示你输入配对码
# 比如 [agent] Passkey: 966940
# 你用键盘输入相应数字回车即可
```


