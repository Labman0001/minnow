#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), closed(false), sum_bytes_buffered(0),
                                              sum_bytes_pushd(0), sum_bytes_popd(0){
  buffer.reserve(capacity);
}

void Writer::push( string data )
{
  int sum = min(capacity_-buffer.size(),data.size());
  if(closed || error_){
    return ;
  }else{
    data = data.substr(0,sum);
    buffer += data;
    sum_bytes_buffered += sum;
    sum_bytes_pushd += sum;
    return;
  }
  return ;
}

void Writer::close()
{
  // Your code here.
  closed = true;
}

bool Writer::is_closed() const
{
 // Your code here.
 return closed;
}

uint64_t Writer::available_capacity() const
{
   // Your code here.
   return capacity_ - buffer.size();
}

uint64_t Writer::bytes_pushed() const
{
 // Your code here.
 return sum_bytes_pushd;
}

string_view Reader::peek() const
{
  // std::string_view peek_buffer;
  // if(!closed){
  //   peek_buffer = buffer;
  // }
  //std::string_view peek_buffer = buffer;
  return buffer;
}

void Reader::pop( uint64_t len )
{
  int sum = min(len,buffer.size());
  buffer.erase(0,sum);
  sum_bytes_popd += sum;
  sum_bytes_buffered -= sum;
}

bool Reader::is_finished() const
{
  // Your code here.
  return closed && buffer.empty();
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return sum_bytes_buffered;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return sum_bytes_popd;
}

