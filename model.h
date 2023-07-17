#ifndef UUID139786138786768
#define UUID139786138786768

#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>

#ifdef __has_attribute
#define HAVE_ATTRIBUTE(x) __has_attribute(x)
#else
#define HAVE_ATTRIBUTE(x) 0
#endif
#if HAVE_ATTRIBUTE(aligned) || (defined(__GNUC__) && !defined(__clang__))
#define DATA_ALIGN_ATTRIBUTE __attribute__((aligned(4)))
#else
#define DATA_ALIGN_ATTRIBUTE
#endif

#ifndef ARENA_SIZE
#define ARENA_SIZE 8096
#endif

/** model size = 275672 bytes **/

/**
 * Wrapper around the EloquentTinyML library
 */
template<uint32_t arenaSize>
class TensorFlowPorter {
    public:
        Eloquent::TinyML::TensorFlow::AllOpsTensorFlow<1350, 5, arenaSize> tf;

        /**
         * Init model
         */
        bool begin() {
            return tf.begin(modelData);
        }

        /**
         * Proxy
         */
        uint8_t predict(uint8_t *input, uint8_t *output = NULL) {
            return tf.predict(input, output);
        }

        /**
         * Proxy
         */
        int8_t predict(int8_t *input, int8_t *output = NULL) {
            return tf.predict(input, output);
        }

        /**
         * Proxy
         */
        float predict(float *input, float *output = NULL) {
            return tf.predict(input, output);
        }

        /**
         * Proxy
         */
        template<typename T>
        uint8_t predictClass(T *input) {
            return tf.predictClass(input);
        }

        /**
         * Proxy
         */
        float getScoreAt(uint8_t index) {
            return tf.getScoreAt(index);
        }

        /**
         * Proxy
         */
        String getErrorMessage() {
            return tf.getErrorMessage();
        }
};



TensorFlowPorter<ARENA_SIZE> MovimientoNN;


#endif