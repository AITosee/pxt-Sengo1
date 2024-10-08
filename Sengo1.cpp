#include "Sengo1.h"

namespace tosee_sentry
{
    Sengo1 sengo1;

    //%
    int sengo1Begin(int mode, int addr)
    {
        if (mode == kI2CMode)
        {
            HwSentryI2C::hw_i2c_t communication_port = 0;
            return sengo1.begin(&communication_port, addr);
        }
        else
        {
            HwSentryUart::hw_uart_t communication_port = 0;
            return sengo1.begin(communication_port, addr);
        }

        return SENTRY_FAIL;
    }

    //%
    int sengo1LedSetColor(int detected_color, int undetected_color, int leval)
    {
        return sengo1.LedSetColor((sentry_led_color_e)detected_color, (sentry_led_color_e)undetected_color, leval);
    }

    //%
    int sengo1SetParamNum(int vision_type, int max_num)
    {
        return sengo1.SetParamNum((Sengo1::sentry_vision_e)vision_type, max_num);
    }

    //%
    int sengo1SetParam(int vision_type, Buffer buff, int param_id)
    {
        if (buff->length == 10)
        {
            sentry_object_t param; 

            param.result_data1 = buff->data[0]<<8|buff->data[1];
            param.result_data2 = buff->data[2]<<8|buff->data[3];
            param.result_data3 = buff->data[4]<<8|buff->data[5];
            param.result_data4 = buff->data[6]<<8|buff->data[7];
            param.result_data5 = buff->data[8]<<8|buff->data[9];

            return sengo1.SetParam((Sengo1::sentry_vision_e)vision_type, &param, param_id);
        }
        
        return SENTRY_FAIL;
    }

    //%
    int sengo1VisionSetStatus(int status, int vision_type)
    {
        if (status)
        {
            return sengo1.VisionBegin((Sengo1::sentry_vision_e)vision_type);
        }
        else
        {
            return sengo1.VisionEnd((Sengo1::sentry_vision_e)vision_type);
        }
    }

    //%
    int sengo1GetValue(int vision_type, int obj, int obj_id)
    {
        return sengo1.GetValue((Sengo1::sentry_vision_e)vision_type, (sentry_obj_info_e)obj, obj_id);
    }

    //%
    String sengo1GetQrCodeValue()
    {
        return PSTR(sengo1.GetQrCodeValue());
    }
}