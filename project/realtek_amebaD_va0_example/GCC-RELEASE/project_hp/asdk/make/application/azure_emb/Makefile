include $(MAKE_INCLUDE_GEN)

.PHONY: all clean

#*****************************************************************************#
#                               VARIABLES                               #
#*****************************************************************************#
DIR = $(BASEDIR)/component/common/application/azure/azure-sdk-for-c

vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                               Source FILE LIST                              #
#*****************************************************************************#

#azure - core
CSRC += $(DIR)/sdk/src/azure/core/az_context.c
CSRC += $(DIR)/sdk/src/azure/core/az_http_pipeline.c
CSRC += $(DIR)/sdk/src/azure/core/az_http_policy.c
CSRC += $(DIR)/sdk/src/azure/core/az_http_policy_logging.c
CSRC += $(DIR)/sdk/src/azure/core/az_http_policy_retry.c
CSRC += $(DIR)/sdk/src/azure/core/az_http_request.c
CSRC += $(DIR)/sdk/src/azure/core/az_http_response.c
CSRC += $(DIR)/sdk/src/azure/core/az_json_reader.c
CSRC += $(DIR)/sdk/src/azure/core/az_json_token.c
CSRC += $(DIR)/sdk/src/azure/core/az_json_writer.c
CSRC += $(DIR)/sdk/src/azure/core/az_log.c
CSRC += $(DIR)/sdk/src/azure/core/az_precondition.c
CSRC += $(DIR)/sdk/src/azure/core/az_span.c

#azure - iot
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_common.c
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_hub_client.c
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_hub_client_c2d.c
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_hub_client_methods.c
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_hub_client_sas.c
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_hub_client_telemetry.c
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_hub_client_twin.c
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_provisioning_client.c
CSRC += $(DIR)/sdk/src/azure/iot/az_iot_provisioning_client_sas.c

#azure - platform
CSRC += $(DIR)/sdk/src/azure/platform/az_ameba.c




#*****************************************************************************#
#                               Object FILE LIST                              #
#*****************************************************************************#
OBJS = $(notdir $(CSRC:.c=.o))

#*****************************************************************************#
#                               Include Dependency                            #
#*****************************************************************************#
-include $(OBJS:.o=.d)


#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#
all: CORE_TARGETS COPY_RAM_OBJS

#*****************************************************************************#
#              GENERATE OBJECT FILE 
#*****************************************************************************#
CORE_TARGETS: $(OBJS)

#*****************************************************************************#
#                        RULES TO CLEAN TARGETS                               #
#*****************************************************************************#
clean: CLEAN_OBJS
	$(REMOVE) *.o
	$(REMOVE) *.i
	$(REMOVE) *.s
	$(REMOVE) *.su
	$(REMOVE) *.d

-include $(DEPS)
