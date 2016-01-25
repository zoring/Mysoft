#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <vector>
using namespace boost::asio;
using boost::system::error_code;
using ip::tcp;
 
using namespace std;

struct CHelloWorld_Service{

 char buffd[512] ;
int offset ;
     CHelloWorld_Service(io_service &iosev)
          :m_iosev(iosev),m_acceptor(iosev, tcp::endpoint(tcp::v4(), 1200))
     {
      }
void start()
     {
 
       // 开始等待连接（非阻塞）
	std::cout<<"Just test1"<<std::endl;
       boost::shared_ptr<tcp::socket>  psocket(new tcp::socket(m_iosev));
 	psockets.push_back(psocket) ;
        // 触发的事件只有error_code参数，所以用boost::bind把socket绑定进去
         m_acceptor.async_accept(*psocket,
             boost::bind(&CHelloWorld_Service::accept_handler, this, psocket, _1)
             );
	std::cout<<"Just test2"<<std::endl;
	return ;
    	}


size_t up_to_enter(const boost::system::error_code& e, size_t bytes) {
for ( size_t i = 0; i < bytes; ++i)
if ( buffd[i + offset] == '\n')
return 0;
return 1;
}
 void on_read(boost::shared_ptr<tcp::socket> psocket, const boost::system::error_code &, size_t bytes) {
cout<<bytes <<endl;
if (bytes == 0)
 return ;
 for (size_t index = 0; index < bytes ;index ++)
 cout<<buffd[index];
cout << endl;
 cout<< "this is reading" <<endl;
psocket->async_read_some(buffer(buffd), boost::bind(&CHelloWorld_Service::on_read, this,psocket, _1, _2));
}

void testd(){
}


    // 有客户端连接时accept_handler触发
    void accept_handler(boost::shared_ptr<tcp::socket> psocket, error_code ec)
      {
        if(ec) return;
        // 继续等待连接
    start();
        // 显示远程IP
        std::cout << psocket->remote_endpoint().address() << std::endl;
        
	psocket->async_read_some(buffer(buffd), boost::bind(&CHelloWorld_Service::on_read, this, psocket,_1, _2));
        // 发送信息(非阻塞)
        boost::shared_ptr<std::string> pstr(new std::string("hello async world!"));
         psocket->async_write_some(buffer(*pstr),
             boost::bind(&CHelloWorld_Service::write_handler, this, pstr, _1, _2)
            );
   

  
        return;
     }
    // 异步写操作完成后write_handler触发
   void write_handler(boost::shared_ptr<std::string> pstr,
         error_code ec, size_t bytes_transferred)
     {
        if(ec)
             std::cout<< "发送失败!" << std::endl;
        else
              std::cout<< *pstr << " 已发送" << std::endl;

      }
private:
     io_service &m_iosev;
     ip::tcp::acceptor m_acceptor;
	vector< boost::shared_ptr<tcp::socket> > psockets;
 };

void runservice(){

   std::cout<<"Just ttd"<<std::endl;
}

 int main()
 {
    io_service iosev;
    CHelloWorld_Service sev(iosev);
	std::cout<<"Just test0"<<std::endl;
    // 开始等待连接
    sev.start();
iosev.run();
	
    return 0;
}

