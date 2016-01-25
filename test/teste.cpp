#include <iostream>
#include <boost/asio.hpp>
#include <string>
using namespace std;
using namespace boost::asio;
int main()
{
     // 所有asio类都需要io_service对象
     io_service iosev;
     // socket对象
     ip::tcp::socket socket(iosev);
     // 连接端点，这里使用了本机连接，可以修改IP地址测试远程连接
      ip::tcp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 1200);
     // 连接服务器
      boost::system::error_code ec;
      socket.connect(ep,ec);

    // 如果出错，打印出错信息
     if(ec)
     {
         std::cout <<"fdsf" <<std::endl;
         std::cout << boost::system::system_error(ec).what() << std::endl;
         return -1;
     }
 int a=8, k=1;
string bufferd;
bufferd = "df" ;
cin>>a;
   while(cin>>a)
   {   
    
	if (!socket.is_open())
	{
	cout<<"socket has closed"<<endl;
	continue;
	}

 	k++;
	cout<<k<<endl;
	stringstream ss;
	ss<<k;
	string t = ss.str();
	bufferd = bufferd + t +"\n";
	cout<<bufferd<<endl;
   	socket.write_some(buffer("反對是否"));
     // 接收数据
      std::cout <<"ffdd开服天数sf" <<std::endl;
  
	}
    
     return 0;
}

