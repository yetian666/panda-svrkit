
//******************************************************************************
// RCF - Remote Call Framework
//
// Copyright (c) 2005 - 2012, Delta V Software. All rights reserved.
// http://www.deltavsoft.com
//
// RCF is distributed under dual licenses - closed source or GPL.
// Consult your particular license for conditions of use.
//
// If you have not purchased a commercial license, you are using RCF 
// under GPL terms.
//
// Version: 2.0
// Contact: support <at> deltavsoft.com 
//
//******************************************************************************

#ifndef INCLUDE_RCF_INPROCESSTRANSPORT_HPP
#define INCLUDE_RCF_INPROCESSTRANSPORT_HPP

#include <RCF/ClientTransport.hpp>
#include <RCF/Export.hpp>
#include <RCF/RcfSession.hpp>

namespace RCF {

    class InProcessRemoteAddress : public I_RemoteAddress
    {
    public:
        InProcessRemoteAddress(InProcessTransport & transport) : mTransport(transport)
        {
        }

    private:

        std::string string() const
        {
            return "In process endpoint.";
        }

        InProcessTransport & mTransport;
    };

    class RCF_EXPORT InProcessTransport : 
        public I_ClientTransport, 
        public I_SessionState, 
        public I_ServerTransport, 
        public I_ServerTransportEx
    {
    public:
        InProcessTransport(RcfServer & server, RcfServer * pCallbackServer = NULL);
        ~InProcessTransport();

        TransportType getTransportType();

    private:

        RcfServer & mServer;
        RcfServer * mpCallbackServer;
        RcfSessionPtr mSessionPtr;
        RcfSessionPtr mOppositeSessionPtr;

        InProcessRemoteAddress mRemoteAddress;

        bool isInProcess();

        void doInProcessCall(ClientStub & clientStub);

        // I_ClientTransport
        std::auto_ptr<I_ClientTransport> clone() const;

        EndpointPtr getEndpointPtr() const;

        int send(
            I_ClientTransportCallback &     clientStub, 
            const std::vector<ByteBuffer> & data, 
            unsigned int                    timeoutMs);

        int receive(
            I_ClientTransportCallback &     clientStub, 
            ByteBuffer &                    byteBuffer, 
            unsigned int                    timeoutMs);

        bool isConnected();

        void connect(
            I_ClientTransportCallback &     clientStub, 
            unsigned int                    timeoutMs);

        void disconnect(
            unsigned int                    timeoutMs);

        void setTransportFilters(
            const std::vector<FilterPtr> &  filters);

        void getTransportFilters(
            std::vector<FilterPtr> &        filters);

        void setTimer(
            boost::uint32_t timeoutMs,
            I_ClientTransportCallback * pClientStub);

        // I_SessionState
        void        postRead();
        ByteBuffer  getReadByteBuffer();
        void        postWrite(std::vector<ByteBuffer> &byteBuffers);
        void        postClose();
        I_ServerTransport & getServerTransport();
        const I_RemoteAddress & getRemoteAddress();
        //void        setTransportFilters(const std::vector<FilterPtr> &filters);
        //void        getTransportFilters(std::vector<FilterPtr> &filters);;

        // I_ServerTransport
        ServerTransportPtr clone();

        // I_ServerTransportEx
        ClientTransportAutoPtr 
            createClientTransport(
            const I_Endpoint &endpoint);

        SessionPtr 
            createServerSession(
            ClientTransportAutoPtr & clientTransportAutoPtr,
            StubEntryPtr stubEntryPtr,
            bool keepClientConnection);

        ClientTransportAutoPtr 
            createClientTransport(
            SessionPtr sessionPtr);

        bool 
            reflect(
            const SessionPtr &sessionPtr1,
            const SessionPtr &sessionPtr2);

        bool 
            isConnected(
            const SessionPtr &sessionPtr);
    };

} // namespace RCF

#endif // ! INCLUDE_RCF_INPROCESSTRANSPORT_HPP
