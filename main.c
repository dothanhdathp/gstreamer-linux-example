#include <gst/gst.h>

int tutorial_main (int argc, char *argv[]) {
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    /* Build the pipeline */
    // pipeline = gst_parse_launch ("playbin uri=file:///absolute/path/to/hoa-tam-tri-ngu.mp4", NULL);
    pipeline = gst_parse_launch (
        "filesrc location=/home/tad/Code/gstreamer-example/hoa-tam-tri-ngu.mp4 ! decodebin name=dec "
        "dec. ! queue ! videoconvert ! x264enc tune=zerolatency bitrate=2000 ! m. "
        "dec. ! queue ! audioconvert ! audioresample ! avenc_aac ! m. "
        "mpegtsmux name=m ! tcpserversink host=0.0.0.0 port=8000",
        NULL
    );
    /* Start playing */
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    /* Wait until error or EOS */
    bus = gst_element_get_bus (pipeline);
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    /* See next tutorial for proper error message handling/parsing */
    if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR) {
        g_printerr ("An error occurred! Re-run with the GST_DEBUG=*:WARN environment variable set for more details.\n");
    }

    /* Free resources */
    gst_message_unref (msg);
    gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
    return 0;
}

int main (int argc, char *argv[]) {
    return tutorial_main (argc, argv);
}