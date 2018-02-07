#pragma once

#include <cassert>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/locale.hpp>

#include <opensslpp/aes_cbc.h>
#include <opensslpp/aes_gcm.h>
#include <opensslpp/base64.h>
#include <opensslpp/random.h>
#include <opensslpp/rsa.h>
#include <opensslpp/sha.h>

#include <pods/binary_serializer.h>
#include <pods/json_serializer.h>
#include <pods/memory_storage.h>
#include <pods/stream_storage.h>
#include <pods/pods.h>
