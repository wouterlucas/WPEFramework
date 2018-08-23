#ifndef ITVPLATFORM_H
#define ITVPLATFORM_H

namespace WPEFramework {
    namespace Exchange {

        struct ISectionParser {
            virtual uint32_t Parse (const uint8_t data[], const uint16 datalength) = 0;
            virtual uint32_t TableUpdate () = 0;
        };

        struct IMetaData {

            enum source {
                DVBT = 0,
                DVBT2,
                DVBC,
                DVBC2,
                DVBS,
                DVBS2,
                DVBH,
                DVBSH,
                ATSC,
                ATSCMH,
                ISDBT,
                ISDBTB,
                ISDBS,
                ISDBC,
                DTMB,
                CMMB,
                TDMB,
                SDMB,
                DVBS2X
            };

            enum type {
                AUDIO = 0,
                VIDEO,
                SUBTITLE,
                TELETEXT,
                COMPOSITE
            };

            enum codec {
                UNKNOWN = 0,
                H264,
                H265,
                AAC
            };

            struct IIterator {
                virtual bool IsValid() const = 0;
                virtual void Reset() = 0;
                virtual bool Next() = 0;
                virtual IMetaData* MetaData() = 0;
            }

            virtual type Type() = 0;
            virtual source Source() = 0;

            struct IDVB : public IMetaData {

                enum spectrum {
                    AUTO,
                    NORMAL,
                    INVERTED
                };

                enum modulation {
                    QAM_MODE_16,
                    QAM_MODE_32,
                    QAM_MODE_64,
                    QAM_MODE_128,
                    QAM_MODE_256,
                    QAM_MODE_512,
                    QAM_MODE_1024,
                    QAM_MODE_2048,
                    QAM_MODE_4096,
                    QAM_MODE_AUTO,
                    SAT_MODE_DVBS,
                    SAT_MODE_QPSKTURBO,
                    SAT_MODE_8PSKTURBO,
                    SAT_MODE_TURBO,
                    SAT_MODE_QPSKLDPC, //Same as DVBS2-QPSK
                    SAT_MODE_8PSKLDPC, //Same as DVB-S2 8PSK
                    SAT_MODE_DVBS216APSK, //DVB-S2 16APSK
                    SAT_MODE_DVBS232APSK, //DVB-S2 32APSK
                    SAT_MODE_LDPC, //Same as DVB-S2
                    SAT_MODE_DVBS2xQPSK,
                    SAT_MODE_DVBS2x8PSK,
                    SAT_MODE_DVBS2x8APSK,
                    SAT_MODE_DVBS2x16APSK,
                    SAT_MODE_DVBS2x32APSK,
                    SAT_MODE_BLINDACQUISITION
                };

                virtual uint32_t Frequency() const = 0;
                virtual uint32_t SymbolRate() const = 0;
                virtual spectrum Spectrum() const = 0;
                virtual modulation Modulation() const = 0;
                virtual uint16_t Pid() const = 0;
                virtual codec Codec() const = 0;
            };

            typedef IDVB IATSC;
        };

        struct IStream {

            struct IIterator {
                virtual bool IsValid() const = 0;
                virtual void Reset() = 0;
                virtual bool Next() = 0;
                virtual IStream* Stream() = 0;
            }

            virtual IStream::IIterator Streams ();
            virtual const IMetaData* MetaData() const = 0;
            virtual ITVPlatform::errorcode Speed(const uint32_t speed) = 0;
        };

        struct IDecoder {

            virtual IStream* Stream ();
            virtual ITVPlatform::errorcode Speed (const sint32_t speed); // 100 is normal playback forward. 0 = pause.
            virtual sint32_t Speed () const; // 100 is normal playback forward. 0 = pause.
        };

        struct IFrontend {

            virtual ITVPlatform::errorcode Tune (const IMetaData* parameters);
            virtual ITVPlatform::errorcode Prime(const IMetaData::IIterator* parameters);
            virtual ITVPlatform::errorcode AddFilter (struct ISectionParser*, uint16_t pid, uint16_t tableId);
            virtual ITVPlatform::errorcode RemoveFilter (struct ISectionParser*);

            virtual IDecoder* Acquire ();
            virtual ITVPlatform::errorcode Release (IDecoder* decoder);
        };

        struct ITVPlatform {

            enum errorcode {
                ERROR_NONE = 0,
                ERROR_NOT_SUPPORTED
            };

            static ITVPlatform* Instance();
            virtual IFrontend* Aquire () = 0;
            virtual ITVPlatform::errorcode Release (IFrontend*) = 0;
        };
    }
}

#endif // ITVPLATFORM_H
