Example Description

This example describes how to use ADC normal channel in comparator-assist mode.
To reduce ADC power consumption , an additional comparator could cooperate with ADC as a first level check of input voltage. 
Once comparison result matches a predefined criterion, a wake-up signal could be delivered to ADC module by comparator. 
ADC module would execute a single conversion to get a voltage value.

In this example, reference voltage is set to 1v (Vref0) and 2v (Vref1). When input voltage of one channel (CH0~4) is between
Vref0 and Vref1, compare criterion matches and wakeup ADC to sample for the channel.
For example, when AD_1 is fed with 1.8v, the system would print the following log:
		AD1:998 = 1832 mv




