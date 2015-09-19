---
layout: post
title: "android_pre"
date: 2015-08-30 07:50:22 -0700
comments: true
categories: 
---
###0x00 安卓环境配置
1.设置
JAVA_HOME  
ANDROID_NDK  
2.安装  
CDT，ADT  
ADT:  
离线：https://dl.google.com/android/ADT-23.0.6.zip  
在线：https://dl-ssl.google.com/android/eclipse
3.设置ECLIPSE  
ndk位置
sdk位置
需要jar：project->propoties->java->build

###0x01 java
###package & import
package就是一个类库单元，包含一组类，他们在单一名称空间下被组织在了一起，这个名称空间就是报名，可以使用import关键字导入一个包


###final
final类有无法改变或终态的含义，它可以修饰非抽象类、非抽象类成员方法和变量。  
final类不能被继承，final类中的方法默认是final的  
final方法不能被子类的方法覆盖，但可以被继承  
final不能用于修饰构造方法  
final修饰的成员变量表示常量

###static
static表示全局或者静态的意思，用来修饰成员变量和方法  
被static修饰的成员变量和方法独立于该类的任何对象。它不依赖类特定的实例，被类的所有实例共享。
同public修饰的static成员变量和成员方法本质是全局变量和全局方法，当声明它类的对象时，不生成static变量的副本，而是所有实例共享一个static变量  
static变量前可以有private修饰，表示这个变量可以在类的静态代码块中

-静态变量   
在内存中只有一份拷贝
-静态方法  
静态方法可以直接通过类名调用  
不能直接访问所属类的实例变量和实例方法,只能访问类的静态成员变量和成员方法  

###super
super来引用父类的成员  
super调用父类的构造方法，一定要放在方法的首个语句


###abstract & interface
接口只能定义方法，不能有方法的实现  
抽象类中既有方法的实现，又有没有具体实现的抽象方法  




###extends & implement
extends是继承父类，只要那个类不是声明为final或者那个类定义为abstract的就能继承  
extends实现父类会覆盖父类的变量或者函数  
implements可以实现多个接口
implements是一个类实现一个接口用的关键字，它是用来实现接口中定义的抽象方法。  
implement实现父类，子类不可以覆盖父类的方法或者变量  

###内部类
1.成员外部类  
成员内部类，就是作为外部类的成员，可以直接使用外部类的所有成员和方法  
成员内部类不能含有static的变量和方法
内部类可以随意食用外部类的成员变量,包括私有
2.匿名内部类  
正因为没有名字，所以匿名内部类只能使用一次，它通常同来简化代码编写  
使用匿名内部类还有个前提条件，必须继承一个父类或实现一个接口

匿名类的基本实现
	abstract class Person {
	    public abstract void eat();
	}
	 
	public class Demo {
	    public static void main(String[] args) {
		Person p = new Person() {
		    public void eat() {
			System.out.println("eat something");
		    }
		};
		p.eat();
	    }
	}

接口

	interface Person {
	    public void eat();
	}
	 
	public class Demo {
	    public static void main(String[] args) {
		Person p = new Person() {
		    public void eat() {
			System.out.println("eat something");
		    }
		};
		p.eat();
	    }
	}

###0x02 常见问题

-安装android support repository 、usb driver  
-ActionBarActivity
This way work for me with Eclipse in Android developer tool from Google -righ click - property - java build path - add external JAR  
point to: android-support-v7-appcompat.jar in /sdk/extras/android/support/v7/appcompat/libs
  

-java方法内不可定义方法  
=finally关键字，finally结构使代码总会执行，而不管有无异常发生  
- IOException  在函数后面加上throws Exception   
加try{}catch{}  
-adb logcat  
日志输出，优先级按下列从低到高排列  
V - Verbose 冗长的  
D - Debug  
I - Info  
W - Warning  
E - Error  
F - Fatal  
S - Silent   
-主线程不能访问网络  
	new Thread(){
	   @Override
	   public void run()
	   {
	   //把网络访问的代码放在这里   
	  }
	}.start();
 

-missing INITERNET permission  
在AndroidManifest.xml添加<uses-permission android:name="android.permission.INTERNET" />  
-handler可以分发Message对象和Runnable对象到主线程，每个Handler实例，都会绑定到创建池的线程中  
-一个java文件只能有一个public类   
-java 异常抛出  
	try{

	}catch(){

	}

-多个设备adb时  
使用-s 加设备名  
-Cannot make a static reference to the non-static method  
调用了非静态方法



	


