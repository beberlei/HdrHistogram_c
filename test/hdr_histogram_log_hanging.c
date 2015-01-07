#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <hdr_histogram.h>
#include <hdr_histogram_log.h>

int main(int argc, char **argv)
{
	struct hdr_histogram *histogram, *new = NULL;
	struct hdr_iter iterator;
	hdr_init(1, 1000 * 60, 3, &histogram);

	for (int i = 1; i < (1000 * 60); i++) {
		hdr_record_values(histogram, i+1, ((1000*60)-i) / 10);
	}

	char *data;

	if (hdr_log_encode(histogram, &data) != 0) {
		printf("error");
		return 1;
	}

	if (hdr_log_decode(&new, data, strlen(data)) != 0) {
		printf("error2");
		return 2;
	}

	hdr_iter_init(&iterator, new);

	while (hdr_iter_next(&iterator) == true) {
		printf("%"PRIu64": %"PRIu64"\n", iterator.value_from_index, iterator.count_at_index);
	}
}
