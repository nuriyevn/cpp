// https://stackoverflow.com/questions/44636240/central-event-dispatcher-with-templated-event-types-in-c
#include <iostream>
#include <map>
#include <vector>

class IEvent
{
public:
    virtual const std::string & getName() const = 0;
};

template <typename ..._args>
class Event: public IEvent
{
public:
    using _callback = std::function<void(_args...)>;

    explicit Event(const std::string &name, const _callback & cb) 
        : _name(name), _cbFunc(cb) 
    {}
    virtual const std::string & getName() const override { return this->_name; }

    void trigger(_args... a) { this->_cbFunc(a...);}

private:
    std::string _name;
    _callback const _cbFunc;
};

class EventDispatcher
{
public:
     EventDispatcher() {}
    ~EventDispatcher()
    {
      for ( auto el : _eventList )
      {
        for ( auto e : el.second )
          delete e;
      }
    }

    void registerEvent(IEvent *event)
    {
        if (event)
            _eventList[event->getName()].push_back( event );
    }

    template <typename ..._args>

private:
    std::map<std::string, std::vector<IEvent*>> _eventList;
};