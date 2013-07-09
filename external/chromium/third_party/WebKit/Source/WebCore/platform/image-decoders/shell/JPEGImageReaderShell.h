/*
 * Copyright 2013 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef JPEGImageReaderShell_h
#define JPEGImageReaderShell_h

#include "ImageReaderShell.h"

namespace WebCore {
    class JPEGImageReaderShell : public ImageReaderShell {
    public:
        static bool matchSignature(const char* signature_str, int str_len)
        {
            const int kSignatureLength = 3;
            if (str_len < kSignatureLength)
                return false;
            return !memcmp(signature_str, "\xFF\xD8\xFF", kSignatureLength);
        }

        virtual String filenameExtension() const OVERRIDE { return "jpg"; }
        virtual String imageTypeString() const OVERRIDE { return "JPEG"; }
    };

    // This function is declared here without the implementation.
    // It is only for caller to know how to create this type of reader.
    // Different platform needs to choose the right reader class to create
    // by implementing this function, and native reader class if necessary.
    JPEGImageReaderShell* createJPEGImageReaderShell();
}
#endif  // JPEGImageReaderShell_h
