// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "test.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* SearchRequest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SearchRequest_reflection_ = NULL;
const ::google::protobuf::Descriptor* SearchResponse_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SearchResponse_reflection_ = NULL;
const ::google::protobuf::ServiceDescriptor* SearchService_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_test_2eproto() {
  protobuf_AddDesc_test_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "test.proto");
  GOOGLE_CHECK(file != NULL);
  SearchRequest_descriptor_ = file->message_type(0);
  static const int SearchRequest_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearchRequest, query_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearchRequest, page_number_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearchRequest, result_per_page_),
  };
  SearchRequest_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SearchRequest_descriptor_,
      SearchRequest::default_instance_,
      SearchRequest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearchRequest, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearchRequest, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SearchRequest));
  SearchResponse_descriptor_ = file->message_type(1);
  static const int SearchResponse_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearchResponse, ret_),
  };
  SearchResponse_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SearchResponse_descriptor_,
      SearchResponse::default_instance_,
      SearchResponse_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearchResponse, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearchResponse, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SearchResponse));
  SearchService_descriptor_ = file->service(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_test_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SearchRequest_descriptor_, &SearchRequest::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SearchResponse_descriptor_, &SearchResponse::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_test_2eproto() {
  delete SearchRequest::default_instance_;
  delete SearchRequest_reflection_;
  delete SearchResponse::default_instance_;
  delete SearchResponse_reflection_;
}

void protobuf_AddDesc_test_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\ntest.proto\"L\n\rSearchRequest\022\r\n\005query\030\001"
    " \002(\t\022\023\n\013page_number\030\002 \001(\005\022\027\n\017result_per_"
    "page\030\003 \001(\005\"\035\n\016SearchResponse\022\013\n\003ret\030\001 \002("
    "\0052:\n\rSearchService\022)\n\006Search\022\016.SearchReq"
    "uest\032\017.SearchResponseB\003\200\001\001", 186);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "test.proto", &protobuf_RegisterTypes);
  SearchRequest::default_instance_ = new SearchRequest();
  SearchResponse::default_instance_ = new SearchResponse();
  SearchRequest::default_instance_->InitAsDefaultInstance();
  SearchResponse::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_test_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_test_2eproto {
  StaticDescriptorInitializer_test_2eproto() {
    protobuf_AddDesc_test_2eproto();
  }
} static_descriptor_initializer_test_2eproto_;


// ===================================================================

#ifndef _MSC_VER
const int SearchRequest::kQueryFieldNumber;
const int SearchRequest::kPageNumberFieldNumber;
const int SearchRequest::kResultPerPageFieldNumber;
#endif  // !_MSC_VER

SearchRequest::SearchRequest()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SearchRequest::InitAsDefaultInstance() {
}

SearchRequest::SearchRequest(const SearchRequest& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SearchRequest::SharedCtor() {
  _cached_size_ = 0;
  query_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  page_number_ = 0;
  result_per_page_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SearchRequest::~SearchRequest() {
  SharedDtor();
}

void SearchRequest::SharedDtor() {
  if (query_ != &::google::protobuf::internal::kEmptyString) {
    delete query_;
  }
  if (this != default_instance_) {
  }
}

void SearchRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SearchRequest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SearchRequest_descriptor_;
}

const SearchRequest& SearchRequest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_test_2eproto();  return *default_instance_;
}

SearchRequest* SearchRequest::default_instance_ = NULL;

SearchRequest* SearchRequest::New() const {
  return new SearchRequest;
}

void SearchRequest::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_query()) {
      if (query_ != &::google::protobuf::internal::kEmptyString) {
        query_->clear();
      }
    }
    page_number_ = 0;
    result_per_page_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SearchRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string query = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_query()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->query().data(), this->query().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_page_number;
        break;
      }
      
      // optional int32 page_number = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_page_number:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &page_number_)));
          set_has_page_number();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_result_per_page;
        break;
      }
      
      // optional int32 result_per_page = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_result_per_page:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &result_per_page_)));
          set_has_result_per_page();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void SearchRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string query = 1;
  if (has_query()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->query().data(), this->query().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->query(), output);
  }
  
  // optional int32 page_number = 2;
  if (has_page_number()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->page_number(), output);
  }
  
  // optional int32 result_per_page = 3;
  if (has_result_per_page()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->result_per_page(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* SearchRequest::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string query = 1;
  if (has_query()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->query().data(), this->query().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->query(), target);
  }
  
  // optional int32 page_number = 2;
  if (has_page_number()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->page_number(), target);
  }
  
  // optional int32 result_per_page = 3;
  if (has_result_per_page()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->result_per_page(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int SearchRequest::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string query = 1;
    if (has_query()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->query());
    }
    
    // optional int32 page_number = 2;
    if (has_page_number()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->page_number());
    }
    
    // optional int32 result_per_page = 3;
    if (has_result_per_page()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->result_per_page());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SearchRequest::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SearchRequest* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SearchRequest*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SearchRequest::MergeFrom(const SearchRequest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_query()) {
      set_query(from.query());
    }
    if (from.has_page_number()) {
      set_page_number(from.page_number());
    }
    if (from.has_result_per_page()) {
      set_result_per_page(from.result_per_page());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SearchRequest::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SearchRequest::CopyFrom(const SearchRequest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SearchRequest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  return true;
}

void SearchRequest::Swap(SearchRequest* other) {
  if (other != this) {
    std::swap(query_, other->query_);
    std::swap(page_number_, other->page_number_);
    std::swap(result_per_page_, other->result_per_page_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SearchRequest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SearchRequest_descriptor_;
  metadata.reflection = SearchRequest_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int SearchResponse::kRetFieldNumber;
#endif  // !_MSC_VER

SearchResponse::SearchResponse()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SearchResponse::InitAsDefaultInstance() {
}

SearchResponse::SearchResponse(const SearchResponse& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SearchResponse::SharedCtor() {
  _cached_size_ = 0;
  ret_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SearchResponse::~SearchResponse() {
  SharedDtor();
}

void SearchResponse::SharedDtor() {
  if (this != default_instance_) {
  }
}

void SearchResponse::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SearchResponse::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SearchResponse_descriptor_;
}

const SearchResponse& SearchResponse::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_test_2eproto();  return *default_instance_;
}

SearchResponse* SearchResponse::default_instance_ = NULL;

SearchResponse* SearchResponse::New() const {
  return new SearchResponse;
}

void SearchResponse::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    ret_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SearchResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 ret = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &ret_)));
          set_has_ret();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void SearchResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 ret = 1;
  if (has_ret()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->ret(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* SearchResponse::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 ret = 1;
  if (has_ret()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->ret(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int SearchResponse::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 ret = 1;
    if (has_ret()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->ret());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SearchResponse::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SearchResponse* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SearchResponse*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SearchResponse::MergeFrom(const SearchResponse& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_ret()) {
      set_ret(from.ret());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SearchResponse::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SearchResponse::CopyFrom(const SearchResponse& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SearchResponse::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  
  return true;
}

void SearchResponse::Swap(SearchResponse* other) {
  if (other != this) {
    std::swap(ret_, other->ret_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SearchResponse::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SearchResponse_descriptor_;
  metadata.reflection = SearchResponse_reflection_;
  return metadata;
}


// ===================================================================

SearchService::~SearchService() {}

const ::google::protobuf::ServiceDescriptor* SearchService::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SearchService_descriptor_;
}

const ::google::protobuf::ServiceDescriptor* SearchService::GetDescriptor() {
  protobuf_AssignDescriptorsOnce();
  return SearchService_descriptor_;
}

void SearchService::Search(::google::protobuf::RpcController* controller,
                         const ::SearchRequest*,
                         ::SearchResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method Search() not implemented.");
  done->Run();
}

void SearchService::CallMethod(const ::google::protobuf::MethodDescriptor* method,
                             ::google::protobuf::RpcController* controller,
                             const ::google::protobuf::Message* request,
                             ::google::protobuf::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), SearchService_descriptor_);
  switch(method->index()) {
    case 0:
      Search(controller,
             ::google::protobuf::down_cast<const ::SearchRequest*>(request),
             ::google::protobuf::down_cast< ::SearchResponse*>(response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::google::protobuf::Message& SearchService::GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::SearchRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *reinterpret_cast< ::google::protobuf::Message*>(NULL);
  }
}

const ::google::protobuf::Message& SearchService::GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::SearchResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *reinterpret_cast< ::google::protobuf::Message*>(NULL);
  }
}

SearchService_Stub::SearchService_Stub(::google::protobuf::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
SearchService_Stub::SearchService_Stub(
    ::google::protobuf::RpcChannel* channel,
    ::google::protobuf::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::google::protobuf::Service::STUB_OWNS_CHANNEL) {}
SearchService_Stub::~SearchService_Stub() {
  if (owns_channel_) delete channel_;
}

void SearchService_Stub::Search(::google::protobuf::RpcController* controller,
                              const ::SearchRequest* request,
                              ::SearchResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
