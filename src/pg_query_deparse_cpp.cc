#include <string.h>
#include <cstdlib>
#include <pg_query.h>

#include <protobuf/pg_query.pb.h>
#include <google/protobuf/util/json_util.h>

extern "C" PgQueryDeparseResult
pg_query_deparse_json(const char *input)
{
    pg_query::ParseResult parse_result;
	PgQueryProtobuf protobuf;
	std::string output;

    google::protobuf::util::JsonStringToMessage(input, &parse_result);
	parse_result.SerializeToString(&output);
	protobuf.data = (char*) calloc(output.size(), sizeof(char));
	protobuf.len = output.size();
	memcpy(protobuf.data, output.data(), output.size());

    PgQueryDeparseResult deparsed = pg_query_deparse_protobuf(protobuf);

    return deparsed;
}