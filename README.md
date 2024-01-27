# Cper

用键盘自动弹奏曲子。

## 介绍

作为一个音乐爱好者，能听到自己亲手弹奏的曲子是一件美妙的事情，可惜四体不勤（手残）不能如愿。这时就需要借助一些其他手段了，比如这个工具。

如果你想演奏一首曲子，这里用`打ち上げ花火`为例，它的前奏是：

G5#、A5#、C6#、F5#（`#`代表升号）

再重复一次，这里可能需要一些乐理知识，不过不了解也没关系，只需要知道在键盘上依次按下哪些键即可。

以AutoPiano为例，是依次按下`Shift+H` `Shift+J` `Shift+L` `Shift+G`。

要一些练习和熟练度，不然就不成曲调了，更何况还需要配上和弦，对于初学者来说未免……太不友好了。

使用**Cper**，一切都简单了起来：

只需创建一个txt文件，将`G5#A5#C6#F5#G5#A5#C6#F5#`写入并保存，**Cper**会自动解析所需按键并按下。和弦也同样如此，<u>score</u>文件夹下提供了例子，*test.txt*是旋律，*test_.txt*是和弦，可稍作参考。

附一些练习网站：

- [Everyone Piano人人钢琴网](https://www.everyonepiano.cn/)

- [AutoPiano](https://www.autopiano.cn/)

- ……

上面提供了虚拟钢琴键盘，用键盘即可进行演奏。

### 其他

一些游戏会将这种玩法集成进去，比如冒险岛2、星球：重启、原神等，作为一个趣味性功能，**Cper**同样能够做到在游戏中演奏你的曲子！只需要你配置好相关的按键映射。

<u>config</u>目录下有一个AutoPinao的映射文件（AutoPiano.ckm），用记事本打开，根据需要修改对应配置项即可：

```
# 音名=键名
# B4按a键
B4=a
…… 
```

保存为*custom.ckm*然后用`-m`参数传入即可，例如：`cpera.exe -m "config\custom.ckm" -t "score\test.txt"`。

## 用法

> 为了物理上模拟按键（更精确地控制以及一些程序会有保护措施），程序使用了驱动。

1. 关闭签名校验，开启调试模式
   
   在Windows10及以上，管理员模式的命令行中，执行如下命令：
   
   `bcdedit /set nointegritychecks on`
   
   `bcdedit /set testsigning on`
   
   需要重启以便生效。

3. 安装驱动
   
   以微软的devcon工具为例，切换到<u>KMDFDriver</u>目录，执行以下命令：
   
   `devcon.exe find "root\hidriver"`
   
   `devcon.exe remove "root\hidriver"`
   
   `devcon.exe install hidriver.inf "root\hidriver"`

5. 命令行执行`cpera.exe -t "score\test.txt","score\test_.txt"`

## 乐谱命令

在乐谱文件中使用。

- \s{值}
  
  设置演奏速度，默认60，即一分钟演奏60个音符。例如\s{100}（一分钟演奏100个音符）

- \d{值}
  
  设置音符时值，默认1/4，即4分音符。例如\s{1/8}（八分音符）

## 目录说明

- dll
  
  dll源码

- exe
  
  可执行文件源码
  
  - config
    
    按键映射配置
  
  - lib
    
    第三方库
  
  - score
    
    乐谱文件（txt/cps）

- lib
  
  lib源码

- sys
  
  驱动程序项目

## 备注

作者没有售卖乐谱，请不要相信。欢迎大家提issue，乐谱文件也可以pr（放在<u>score</u>目录下）。

驱动代码部分只修改了部分配置，感谢驱动程序原作者的开源奉献。
