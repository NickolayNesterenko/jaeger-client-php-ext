/**
 * Autogenerated by Thrift Compiler (0.10.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "thrift-gen/Agent.h"

Agent_emitZipkinBatch_args::~Agent_emitZipkinBatch_args() noexcept {
}

Agent_emitZipkinBatch_pargs::~Agent_emitZipkinBatch_pargs() noexcept {
}

uint32_t Agent_emitZipkinBatch_pargs::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Agent_emitZipkinBatch_pargs");

  xfer += oprot->writeFieldBegin("spans", ::apache::thrift::protocol::T_LIST, 1);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>((*(this->spans)).size()));
    std::vector< ::Span> ::const_iterator _iter6;
    for (_iter6 = (*(this->spans)).begin(); _iter6 != (*(this->spans)).end(); ++_iter6)
    {
      xfer += (*_iter6).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

Agent_emitBatch_pargs::~Agent_emitBatch_pargs() noexcept {
}

uint32_t Agent_emitBatch_pargs::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Agent_emitBatch_pargs");

  xfer += oprot->writeFieldBegin("batch", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += (*(this->batch)).write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void AgentClient::emitZipkinBatch(const std::vector< ::Span> & spans)
{
  send_emitZipkinBatch(spans);
}

void AgentClient::send_emitZipkinBatch(const std::vector< ::Span> & spans)
{
  int32_t cseqid = 0;
  oprot_->writeMessageBegin("emitZipkinBatch", ::apache::thrift::protocol::T_ONEWAY, cseqid);

  Agent_emitZipkinBatch_pargs args;
  args.spans = &spans;
  args.write(oprot_);

  oprot_->writeMessageEnd();
  oprot_->getTransport()->writeEnd();
  oprot_->getTransport()->flush();
}

void AgentClient::emitBatch(const  ::Batch& batch)
{
  send_emitBatch(batch);
}

void AgentClient::send_emitBatch(const  ::Batch& batch)
{
  int32_t cseqid = 0;
  oprot_->writeMessageBegin("emitBatch", ::apache::thrift::protocol::T_ONEWAY, cseqid);

  Agent_emitBatch_pargs args;
  args.batch = &batch;
  args.write(oprot_);

  oprot_->writeMessageEnd();
  oprot_->getTransport()->writeEnd();
  oprot_->getTransport()->flush();
}