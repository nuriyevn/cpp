#include <string>
using namespace std;  
// Опережающее объявление
class LoggerImpl;
  
class Logger
{
  public:    
    Logger( LoggerImpl* p );
    virtual ~Logger( );
    virtual void log( string & str ) = 0;
  protected:
    LoggerImpl * pimpl;
};
  
class ConsoleLogger : public Logger
{
  public:    
    ConsoleLogger();
    void log( string & str );
};
  
class FileLogger : public Logger
{
  public:    
    FileLogger( string & file_name );
    void log( string & str );
  private:
    string file;
};
  
class SocketLogger : public Logger
{
  public:    
    SocketLogger( string & remote_host, int remote_port );
    void log( string & str );
  private:
    string host;
    int    port;
};
