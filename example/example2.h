#ifndef EXAMPLE2_H
#define EXAMPLE2_H
#include <stdexcept>
#include <functional>
#include <map>

namespace reflection {
  template<class T>
  struct Enum {};
}

// ---------------------------
// std::errc : int ( address_family_not_supported address_in_use address_not_available already_connected argument_list_too_long argument_out_of_domain bad_address bad_file_descriptor bad_message broken_pipe connection_aborted connection_already_in_progress connection_refused connection_reset cross_device_link destination_address_required device_or_resource_busy directory_not_empty executable_format_error file_exists file_too_large filename_too_long function_not_supported host_unreachable identifier_removed illegal_byte_sequence inappropriate_io_control_operation interrupted invalid_argument invalid_seek io_error is_a_directory message_size network_down network_reset network_unreachable no_buffer_space no_child_process no_link no_lock_available no_message_available no_message no_protocol_option no_space_on_device no_stream_resources no_such_device_or_address no_such_device no_such_file_or_directory no_such_process not_a_directory not_a_socket not_a_stream not_connected not_enough_memory not_supported operation_canceled operation_in_progress operation_not_permitted operation_not_supported operation_would_block owner_dead permission_denied protocol_error protocol_not_supported read_only_file_system resource_deadlock_would_occur resource_unavailable_try_again result_out_of_range state_not_recoverable stream_timeout text_file_busy timed_out too_many_files_open_in_system too_many_files_open too_many_links too_many_symbolic_link_levels value_too_large wrong_protocol_type ) @ /usr/lib/gcc/x86_64-linux-gnu/4.8/../../../../include/x86_64-linux-gnu/c++/4.8/bits/error_constants.h:40:3
// ---------------------------
namespace reflection {
  template<>
  struct Enum<std::errc> {
    using int_type  = int;
    using enum_type = std::errc;
    static void for_each_possible_value(std::function<void(std::errc)> f) {
      f(std::errc::address_family_not_supported);
      f(std::errc::address_in_use);
      f(std::errc::address_not_available);
      f(std::errc::already_connected);
      f(std::errc::argument_list_too_long);
      f(std::errc::argument_out_of_domain);
      f(std::errc::bad_address);
      f(std::errc::bad_file_descriptor);
      f(std::errc::bad_message);
      f(std::errc::broken_pipe);
      f(std::errc::connection_aborted);
      f(std::errc::connection_already_in_progress);
      f(std::errc::connection_refused);
      f(std::errc::connection_reset);
      f(std::errc::cross_device_link);
      f(std::errc::destination_address_required);
      f(std::errc::device_or_resource_busy);
      f(std::errc::directory_not_empty);
      f(std::errc::executable_format_error);
      f(std::errc::file_exists);
      f(std::errc::file_too_large);
      f(std::errc::filename_too_long);
      f(std::errc::function_not_supported);
      f(std::errc::host_unreachable);
      f(std::errc::identifier_removed);
      f(std::errc::illegal_byte_sequence);
      f(std::errc::inappropriate_io_control_operation);
      f(std::errc::interrupted);
      f(std::errc::invalid_argument);
      f(std::errc::invalid_seek);
      f(std::errc::io_error);
      f(std::errc::is_a_directory);
      f(std::errc::message_size);
      f(std::errc::network_down);
      f(std::errc::network_reset);
      f(std::errc::network_unreachable);
      f(std::errc::no_buffer_space);
      f(std::errc::no_child_process);
      f(std::errc::no_link);
      f(std::errc::no_lock_available);
      f(std::errc::no_message_available);
      f(std::errc::no_message);
      f(std::errc::no_protocol_option);
      f(std::errc::no_space_on_device);
      f(std::errc::no_stream_resources);
      f(std::errc::no_such_device_or_address);
      f(std::errc::no_such_device);
      f(std::errc::no_such_file_or_directory);
      f(std::errc::no_such_process);
      f(std::errc::not_a_directory);
      f(std::errc::not_a_socket);
      f(std::errc::not_a_stream);
      f(std::errc::not_connected);
      f(std::errc::not_enough_memory);
      f(std::errc::not_supported);
      f(std::errc::operation_canceled);
      f(std::errc::operation_in_progress);
      f(std::errc::operation_not_permitted);
      f(std::errc::operation_not_supported);
      f(std::errc::operation_would_block);
      f(std::errc::owner_dead);
      f(std::errc::permission_denied);
      f(std::errc::protocol_error);
      f(std::errc::protocol_not_supported);
      f(std::errc::read_only_file_system);
      f(std::errc::resource_deadlock_would_occur);
      f(std::errc::resource_unavailable_try_again);
      f(std::errc::result_out_of_range);
      f(std::errc::state_not_recoverable);
      f(std::errc::stream_timeout);
      f(std::errc::text_file_busy);
      f(std::errc::timed_out);
      f(std::errc::too_many_files_open_in_system);
      f(std::errc::too_many_files_open);
      f(std::errc::too_many_links);
      f(std::errc::too_many_symbolic_link_levels);
      f(std::errc::value_too_large);
      f(std::errc::wrong_protocol_type);
    }

    static const char* str(std::errc v) {
      auto r = get_value_name_map().find(v);
      if (r!=get_value_name_map().end()) {
        return r->second.c_str();
      }
      else {
        throw std::invalid_argument("unexpected enum value");
      }
    }
    static std::errc parse(const char* txt) {
      auto r = get_name_value_map().find(txt);
      if (r!=get_name_value_map().end()) {
        return r->second;
      }
      else {
        throw std::invalid_argument("text did not match any enum value representation");
      }
    }

  private:
    static const std::map<std::errc, std::string>& get_value_name_map() {
      static std::map<std::errc, std::string> m({
        {std::errc::address_family_not_supported, "address_family_not_supported"},
        {std::errc::address_in_use, "address_in_use"},
        {std::errc::address_not_available, "address_not_available"},
        {std::errc::already_connected, "already_connected"},
        {std::errc::argument_list_too_long, "argument_list_too_long"},
        {std::errc::argument_out_of_domain, "argument_out_of_domain"},
        {std::errc::bad_address, "bad_address"},
        {std::errc::bad_file_descriptor, "bad_file_descriptor"},
        {std::errc::bad_message, "bad_message"},
        {std::errc::broken_pipe, "broken_pipe"},
        {std::errc::connection_aborted, "connection_aborted"},
        {std::errc::connection_already_in_progress, "connection_already_in_progress"},
        {std::errc::connection_refused, "connection_refused"},
        {std::errc::connection_reset, "connection_reset"},
        {std::errc::cross_device_link, "cross_device_link"},
        {std::errc::destination_address_required, "destination_address_required"},
        {std::errc::device_or_resource_busy, "device_or_resource_busy"},
        {std::errc::directory_not_empty, "directory_not_empty"},
        {std::errc::executable_format_error, "executable_format_error"},
        {std::errc::file_exists, "file_exists"},
        {std::errc::file_too_large, "file_too_large"},
        {std::errc::filename_too_long, "filename_too_long"},
        {std::errc::function_not_supported, "function_not_supported"},
        {std::errc::host_unreachable, "host_unreachable"},
        {std::errc::identifier_removed, "identifier_removed"},
        {std::errc::illegal_byte_sequence, "illegal_byte_sequence"},
        {std::errc::inappropriate_io_control_operation, "inappropriate_io_control_operation"},
        {std::errc::interrupted, "interrupted"},
        {std::errc::invalid_argument, "invalid_argument"},
        {std::errc::invalid_seek, "invalid_seek"},
        {std::errc::io_error, "io_error"},
        {std::errc::is_a_directory, "is_a_directory"},
        {std::errc::message_size, "message_size"},
        {std::errc::network_down, "network_down"},
        {std::errc::network_reset, "network_reset"},
        {std::errc::network_unreachable, "network_unreachable"},
        {std::errc::no_buffer_space, "no_buffer_space"},
        {std::errc::no_child_process, "no_child_process"},
        {std::errc::no_link, "no_link"},
        {std::errc::no_lock_available, "no_lock_available"},
        {std::errc::no_message_available, "no_message_available"},
        {std::errc::no_message, "no_message"},
        {std::errc::no_protocol_option, "no_protocol_option"},
        {std::errc::no_space_on_device, "no_space_on_device"},
        {std::errc::no_stream_resources, "no_stream_resources"},
        {std::errc::no_such_device_or_address, "no_such_device_or_address"},
        {std::errc::no_such_device, "no_such_device"},
        {std::errc::no_such_file_or_directory, "no_such_file_or_directory"},
        {std::errc::no_such_process, "no_such_process"},
        {std::errc::not_a_directory, "not_a_directory"},
        {std::errc::not_a_socket, "not_a_socket"},
        {std::errc::not_a_stream, "not_a_stream"},
        {std::errc::not_connected, "not_connected"},
        {std::errc::not_enough_memory, "not_enough_memory"},
        {std::errc::not_supported, "not_supported"},
        {std::errc::operation_canceled, "operation_canceled"},
        {std::errc::operation_in_progress, "operation_in_progress"},
        {std::errc::operation_not_permitted, "operation_not_permitted"},
        {std::errc::operation_not_supported, "operation_not_supported"},
        {std::errc::operation_would_block, "operation_would_block"},
        {std::errc::owner_dead, "owner_dead"},
        {std::errc::permission_denied, "permission_denied"},
        {std::errc::protocol_error, "protocol_error"},
        {std::errc::protocol_not_supported, "protocol_not_supported"},
        {std::errc::read_only_file_system, "read_only_file_system"},
        {std::errc::resource_deadlock_would_occur, "resource_deadlock_would_occur"},
        {std::errc::resource_unavailable_try_again, "resource_unavailable_try_again"},
        {std::errc::result_out_of_range, "result_out_of_range"},
        {std::errc::state_not_recoverable, "state_not_recoverable"},
        {std::errc::stream_timeout, "stream_timeout"},
        {std::errc::text_file_busy, "text_file_busy"},
        {std::errc::timed_out, "timed_out"},
        {std::errc::too_many_files_open_in_system, "too_many_files_open_in_system"},
        {std::errc::too_many_files_open, "too_many_files_open"},
        {std::errc::too_many_links, "too_many_links"},
        {std::errc::too_many_symbolic_link_levels, "too_many_symbolic_link_levels"},
        {std::errc::value_too_large, "value_too_large"},
        {std::errc::wrong_protocol_type, "wrong_protocol_type"},
      });
      return m;
    }
    static const std::map<std::string, std::errc>& get_name_value_map() {
      static std::map<std::string, std::errc> m({
        {"address_family_not_supported",std::errc::address_family_not_supported},
        {"address_in_use",std::errc::address_in_use},
        {"address_not_available",std::errc::address_not_available},
        {"already_connected",std::errc::already_connected},
        {"argument_list_too_long",std::errc::argument_list_too_long},
        {"argument_out_of_domain",std::errc::argument_out_of_domain},
        {"bad_address",std::errc::bad_address},
        {"bad_file_descriptor",std::errc::bad_file_descriptor},
        {"bad_message",std::errc::bad_message},
        {"broken_pipe",std::errc::broken_pipe},
        {"connection_aborted",std::errc::connection_aborted},
        {"connection_already_in_progress",std::errc::connection_already_in_progress},
        {"connection_refused",std::errc::connection_refused},
        {"connection_reset",std::errc::connection_reset},
        {"cross_device_link",std::errc::cross_device_link},
        {"destination_address_required",std::errc::destination_address_required},
        {"device_or_resource_busy",std::errc::device_or_resource_busy},
        {"directory_not_empty",std::errc::directory_not_empty},
        {"executable_format_error",std::errc::executable_format_error},
        {"file_exists",std::errc::file_exists},
        {"file_too_large",std::errc::file_too_large},
        {"filename_too_long",std::errc::filename_too_long},
        {"function_not_supported",std::errc::function_not_supported},
        {"host_unreachable",std::errc::host_unreachable},
        {"identifier_removed",std::errc::identifier_removed},
        {"illegal_byte_sequence",std::errc::illegal_byte_sequence},
        {"inappropriate_io_control_operation",std::errc::inappropriate_io_control_operation},
        {"interrupted",std::errc::interrupted},
        {"invalid_argument",std::errc::invalid_argument},
        {"invalid_seek",std::errc::invalid_seek},
        {"io_error",std::errc::io_error},
        {"is_a_directory",std::errc::is_a_directory},
        {"message_size",std::errc::message_size},
        {"network_down",std::errc::network_down},
        {"network_reset",std::errc::network_reset},
        {"network_unreachable",std::errc::network_unreachable},
        {"no_buffer_space",std::errc::no_buffer_space},
        {"no_child_process",std::errc::no_child_process},
        {"no_link",std::errc::no_link},
        {"no_lock_available",std::errc::no_lock_available},
        {"no_message_available",std::errc::no_message_available},
        {"no_message",std::errc::no_message},
        {"no_protocol_option",std::errc::no_protocol_option},
        {"no_space_on_device",std::errc::no_space_on_device},
        {"no_stream_resources",std::errc::no_stream_resources},
        {"no_such_device_or_address",std::errc::no_such_device_or_address},
        {"no_such_device",std::errc::no_such_device},
        {"no_such_file_or_directory",std::errc::no_such_file_or_directory},
        {"no_such_process",std::errc::no_such_process},
        {"not_a_directory",std::errc::not_a_directory},
        {"not_a_socket",std::errc::not_a_socket},
        {"not_a_stream",std::errc::not_a_stream},
        {"not_connected",std::errc::not_connected},
        {"not_enough_memory",std::errc::not_enough_memory},
        {"not_supported",std::errc::not_supported},
        {"operation_canceled",std::errc::operation_canceled},
        {"operation_in_progress",std::errc::operation_in_progress},
        {"operation_not_permitted",std::errc::operation_not_permitted},
        {"operation_not_supported",std::errc::operation_not_supported},
        {"operation_would_block",std::errc::operation_would_block},
        {"owner_dead",std::errc::owner_dead},
        {"permission_denied",std::errc::permission_denied},
        {"protocol_error",std::errc::protocol_error},
        {"protocol_not_supported",std::errc::protocol_not_supported},
        {"read_only_file_system",std::errc::read_only_file_system},
        {"resource_deadlock_would_occur",std::errc::resource_deadlock_would_occur},
        {"resource_unavailable_try_again",std::errc::resource_unavailable_try_again},
        {"result_out_of_range",std::errc::result_out_of_range},
        {"state_not_recoverable",std::errc::state_not_recoverable},
        {"stream_timeout",std::errc::stream_timeout},
        {"text_file_busy",std::errc::text_file_busy},
        {"timed_out",std::errc::timed_out},
        {"too_many_files_open_in_system",std::errc::too_many_files_open_in_system},
        {"too_many_files_open",std::errc::too_many_files_open},
        {"too_many_links",std::errc::too_many_links},
        {"too_many_symbolic_link_levels",std::errc::too_many_symbolic_link_levels},
        {"value_too_large",std::errc::value_too_large},
        {"wrong_protocol_type",std::errc::wrong_protocol_type},
      });
      return m;
    }

  };
}
std::ostream& operator<< (std::ostream& mystream, const std::errc& myvalue) {
  mystream << reflection::Enum<std::errc>::str(myvalue);
  return mystream;
}


#endif

