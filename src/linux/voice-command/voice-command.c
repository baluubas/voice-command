#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/select.h>

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>

#include "pocketsphinx.h"

static ps_decoder_t *ps;
static cmd_ln_t *config;

static void sleep_msec(int32 ms)
{
    struct timeval tmo;

    tmo.tv_sec = 0;
    tmo.tv_usec = ms * 1000;

    select(0, NULL, NULL, NULL, &tmo);
}

static void recognize_from_microphone()
{
    ad_rec_t *ad;
    int16 adbuf[2048];
    uint8 utt_started, in_speech;
    int32 k;
    char const *hyp;

    if ((ad = ad_open_dev("default",
                          (int) cmd_ln_float32_r(config,
                                                 "-samprate"))) == NULL)
        E_FATAL("Failed to open audio device\n");
    if (ad_start_rec(ad) < 0)
        E_FATAL("Failed to start recording\n");

    if (ps_start_utt(ps) < 0)
        E_FATAL("Failed to start utterance\n");
    utt_started = FALSE;

    for (;;) {
        if ((k = ad_read(ad, adbuf, 2048)) < 0)
            E_FATAL("Failed to read audio\n");
        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        in_speech = ps_get_in_speech(ps);
        if (in_speech && !utt_started) {
            utt_started = TRUE;
        }
        if (!in_speech && utt_started) {
            /* speech -> silence transition, time to start new utterance  */
            ps_end_utt(ps);
            hyp = ps_get_hyp(ps, NULL );
            if (hyp != NULL)
                printf("%s\n", hyp);

            if (ps_start_utt(ps) < 0)
                E_FATAL("Failed to start utterance\n");
            utt_started = FALSE;
        }
        sleep_msec(100);
    }
    ad_close(ad);
}

int main(int argc, char *argv[])
{
    //err_set_logfp(NULL);
    char const *cfg;

    config = cmd_ln_init(NULL, ps_args(), TRUE,
	     "-hmm", MODELDIR "/en-us/en-us",
	     "-lm", MODELDIR "/en-us/en-us.lm.dmp",
	     "-dict", MODELDIR "/en-us/cmudict-en-us.dict",
	     "-samprate", "16000/8000/48000",
	     NULL);

    ps = ps_init(config);
    if (ps == NULL) {
        cmd_ln_free_r(config);
        return 1;
    }

    ps_set_kws(ps, "hello world");
    ps_set_search(ps, "keywords");	
    recognize_from_microphone();

    ps_free(ps);
    cmd_ln_free_r(config);

    return 0;
}

