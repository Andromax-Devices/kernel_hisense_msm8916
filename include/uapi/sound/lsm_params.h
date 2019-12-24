#ifndef _UAPI_LSM_PARAMS_H__
#define _UAPI_LSM_PARAMS_H__

#include <linux/types.h>
#include <sound/asound.h>

#define SNDRV_LSM_VERSION SNDRV_PROTOCOL_VERSION(0, 1, 0)

enum lsm_app_id {
	LSM_VOICE_WAKEUP_APP_ID = 1,
	LSM_VOICE_WAKEUP_APP_ID_V2 = 2,
};

enum lsm_detection_mode {
	LSM_MODE_KEYWORD_ONLY_DETECTION = 1,
	LSM_MODE_USER_KEYWORD_DETECTION
};

enum lsm_vw_status {
	LSM_VOICE_WAKEUP_STATUS_RUNNING = 1,
	LSM_VOICE_WAKEUP_STATUS_DETECTED,
	LSM_VOICE_WAKEUP_STATUS_END_SPEECH,
	LSM_VOICE_WAKEUP_STATUS_REJECTED
};

struct snd_lsm_sound_model {
	__u8 __user *data;
	__u32 data_size;
	enum lsm_detection_mode detection_mode;
	__u16 min_keyw_confidence;
	__u16 min_user_confidence;
	bool detect_failure;
};

enum LSM_PARAM_TYPE {
	LSM_ENDPOINT_DETECT_THRESHOLD = 0,
	LSM_OPERATION_MODE,
	LSM_GAIN,
	LSM_MIN_CONFIDENCE_LEVELS,
	LSM_REG_SND_MODEL,
	LSM_DEREG_SND_MODEL,
	LSM_CUSTOM_PARAMS,
	LSM_POLLING_ENABLE,
	/* driver ioctl will parse only so many params */
	LSM_PARAMS_MAX,
};

/*
 * Data for LSM_ENDPOINT_DETECT_THRESHOLD param_type
 * @epd_begin: Begin threshold
 * @epd_end: End threshold
 */
struct snd_lsm_ep_det_thres {
	__u32 epd_begin;
	__u32 epd_end;
};

/*
 * Data for LSM_OPERATION_MODE param_type
 * @mode: The detection mode to be used
 * @detect_failure: Setting to enable failure detections.
 */
struct snd_lsm_detect_mode {
	enum lsm_detection_mode mode;
	bool detect_failure;
};

/*
 * Data for LSM_GAIN param_type
 * @gain: The gain to be applied on LSM
 */
struct snd_lsm_gain {
	__u16 gain;
};

/*
 * Data for LSM_POLLING_ENABLE param_type
 * @poll_en: Polling enable or disable
 */
struct snd_lsm_poll_enable {
	bool poll_en;
};


struct snd_lsm_sound_model_v2 {
	__u8 __user *data;
	__u8 *confidence_level;
	__u32 data_size;
	enum lsm_detection_mode detection_mode;
	__u8 num_confidence_levels;
	bool detect_failure;
};

struct snd_lsm_session_data {
	enum lsm_app_id app_id;
};

struct snd_lsm_event_status {
	__u16 status;
	__u16 payload_size;
	__u8 payload[0];
};

struct snd_lsm_detection_params {
	__u8 *conf_level;
	enum lsm_detection_mode detect_mode;
	__u8 num_confidence_levels;
	bool detect_failure;
	bool poll_enable;
};

#define SNDRV_LSM_REG_SND_MODEL	 _IOW('U', 0x00, struct snd_lsm_sound_model)
#define SNDRV_LSM_DEREG_SND_MODEL _IOW('U', 0x01, int)
#define SNDRV_LSM_EVENT_STATUS	_IOW('U', 0x02, struct snd_lsm_event_status)
#define SNDRV_LSM_ABORT_EVENT	_IOW('U', 0x03, int)
#define SNDRV_LSM_START		_IOW('U', 0x04, int)
#define SNDRV_LSM_STOP		_IOW('U', 0x05, int)
#define SNDRV_LSM_SET_SESSION_DATA _IOW('U', 0x06, struct snd_lsm_session_data)
#define SNDRV_LSM_REG_SND_MODEL_V2 _IOW('U', 0x07,\
					struct snd_lsm_sound_model_v2)
#define SNDRV_LSM_LAB_CONTROL	_IOW('U', 0x08, uint32_t)
#define SNDRV_LSM_STOP_LAB	_IO('U', 0x09)
#define SNDRV_LSM_SET_PARAMS	_IOW('U', 0x0A, \
					struct snd_lsm_detection_params)

#endif
