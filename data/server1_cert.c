const char test_server1_cert[] = { 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x42, 0x45,
        0x47, 0x49, 0x4e, 0x20, 0x43, 0x45, 0x52, 0x54, 0x49, 0x46, 0x49, 0x43,
        0x41, 0x54, 0x45, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x4d, 0x49, 0x49,
        0x43, 0x6e, 0x44, 0x43, 0x43, 0x41, 0x67, 0x57, 0x67, 0x41, 0x77, 0x49,
        0x42, 0x41, 0x67, 0x49, 0x42, 0x42, 0x7a, 0x41, 0x4e, 0x42, 0x67, 0x6b,
        0x71, 0x68, 0x6b, 0x69, 0x47, 0x39, 0x77, 0x30, 0x42, 0x41, 0x51, 0x73,
        0x46, 0x41, 0x44, 0x42, 0x57, 0x4d, 0x51, 0x73, 0x77, 0x43, 0x51, 0x59,
        0x44, 0x56, 0x51, 0x51, 0x47, 0x45, 0x77, 0x4a, 0x42, 0x56, 0x54, 0x45,
        0x54, 0x0a, 0x4d, 0x42, 0x45, 0x47, 0x41, 0x31, 0x55, 0x45, 0x43, 0x42,
        0x4d, 0x4b, 0x55, 0x32, 0x39, 0x74, 0x5a, 0x53, 0x31, 0x54, 0x64, 0x47,
        0x46, 0x30, 0x5a, 0x54, 0x45, 0x68, 0x4d, 0x42, 0x38, 0x47, 0x41, 0x31,
        0x55, 0x45, 0x43, 0x68, 0x4d, 0x59, 0x53, 0x57, 0x35, 0x30, 0x5a, 0x58,
        0x4a, 0x75, 0x5a, 0x58, 0x51, 0x67, 0x56, 0x32, 0x6c, 0x6b, 0x5a, 0x32,
        0x6c, 0x30, 0x63, 0x79, 0x42, 0x51, 0x0a, 0x64, 0x48, 0x6b, 0x67, 0x54,
        0x48, 0x52, 0x6b, 0x4d, 0x51, 0x38, 0x77, 0x44, 0x51, 0x59, 0x44, 0x56,
        0x51, 0x51, 0x44, 0x45, 0x77, 0x5a, 0x30, 0x5a, 0x58, 0x4e, 0x30, 0x59,
        0x32, 0x45, 0x77, 0x48, 0x68, 0x63, 0x4e, 0x4d, 0x54, 0x55, 0x78, 0x4d,
        0x54, 0x41, 0x30, 0x4d, 0x44, 0x49, 0x79, 0x4d, 0x44, 0x49, 0x30, 0x57,
        0x68, 0x63, 0x4e, 0x4d, 0x6a, 0x55, 0x78, 0x4d, 0x54, 0x41, 0x78, 0x0a,
        0x4d, 0x44, 0x49, 0x79, 0x4d, 0x44, 0x49, 0x30, 0x57, 0x6a, 0x42, 0x6c,
        0x4d, 0x51, 0x73, 0x77, 0x43, 0x51, 0x59, 0x44, 0x56, 0x51, 0x51, 0x47,
        0x45, 0x77, 0x4a, 0x56, 0x55, 0x7a, 0x45, 0x52, 0x4d, 0x41, 0x38, 0x47,
        0x41, 0x31, 0x55, 0x45, 0x43, 0x42, 0x4d, 0x49, 0x53, 0x57, 0x78, 0x73,
        0x61, 0x57, 0x35, 0x76, 0x61, 0x58, 0x4d, 0x78, 0x45, 0x44, 0x41, 0x4f,
        0x42, 0x67, 0x4e, 0x56, 0x0a, 0x42, 0x41, 0x63, 0x54, 0x42, 0x30, 0x4e,
        0x6f, 0x61, 0x57, 0x4e, 0x68, 0x5a, 0x32, 0x38, 0x78, 0x46, 0x54, 0x41,
        0x54, 0x42, 0x67, 0x4e, 0x56, 0x42, 0x41, 0x6f, 0x54, 0x44, 0x45, 0x56,
        0x34, 0x59, 0x57, 0x31, 0x77, 0x62, 0x47, 0x55, 0x73, 0x49, 0x45, 0x4e,
        0x76, 0x4c, 0x6a, 0x45, 0x61, 0x4d, 0x42, 0x67, 0x47, 0x41, 0x31, 0x55,
        0x45, 0x41, 0x78, 0x51, 0x52, 0x4b, 0x69, 0x35, 0x30, 0x0a, 0x5a, 0x58,
        0x4e, 0x30, 0x4c, 0x6d, 0x64, 0x76, 0x62, 0x32, 0x64, 0x73, 0x5a, 0x53,
        0x35, 0x6a, 0x62, 0x32, 0x30, 0x77, 0x67, 0x5a, 0x38, 0x77, 0x44, 0x51,
        0x59, 0x4a, 0x4b, 0x6f, 0x5a, 0x49, 0x68, 0x76, 0x63, 0x4e, 0x41, 0x51,
        0x45, 0x42, 0x42, 0x51, 0x41, 0x44, 0x67, 0x59, 0x30, 0x41, 0x4d, 0x49,
        0x47, 0x4a, 0x41, 0x6f, 0x47, 0x42, 0x41, 0x4f, 0x48, 0x44, 0x46, 0x53,
        0x63, 0x6f, 0x0a, 0x4c, 0x43, 0x56, 0x4a, 0x70, 0x59, 0x44, 0x44, 0x4d,
        0x34, 0x48, 0x59, 0x74, 0x49, 0x64, 0x56, 0x36, 0x41, 0x6b, 0x65, 0x2f,
        0x73, 0x4d, 0x4e, 0x61, 0x61, 0x4b, 0x64, 0x4f, 0x44, 0x6a, 0x44, 0x4d,
        0x73, 0x75, 0x78, 0x2f, 0x34, 0x74, 0x44, 0x79, 0x64, 0x6c, 0x75, 0x6d,
        0x4e, 0x2b, 0x66, 0x6d, 0x2b, 0x41, 0x6a, 0x50, 0x45, 0x4b, 0x35, 0x47,
        0x48, 0x68, 0x47, 0x6e, 0x31, 0x42, 0x67, 0x0a, 0x7a, 0x6b, 0x57, 0x46,
        0x2b, 0x73, 0x6c, 0x66, 0x33, 0x42, 0x78, 0x68, 0x72, 0x41, 0x2f, 0x38,
        0x64, 0x4e, 0x73, 0x6e, 0x75, 0x6e, 0x73, 0x74, 0x56, 0x41, 0x37, 0x5a,
        0x42, 0x67, 0x41, 0x2f, 0x35, 0x71, 0x51, 0x78, 0x4d, 0x66, 0x47, 0x41,
        0x71, 0x34, 0x77, 0x48, 0x4e, 0x56, 0x58, 0x37, 0x37, 0x66, 0x42, 0x5a,
        0x4f, 0x67, 0x70, 0x39, 0x56, 0x6c, 0x53, 0x4d, 0x56, 0x66, 0x79, 0x64,
        0x0a, 0x39, 0x4e, 0x38, 0x59, 0x77, 0x62, 0x42, 0x59, 0x41, 0x63, 0x6b,
        0x4f, 0x65, 0x55, 0x51, 0x61, 0x64, 0x54, 0x69, 0x32, 0x58, 0x31, 0x53,
        0x36, 0x4f, 0x67, 0x4a, 0x58, 0x67, 0x51, 0x30, 0x6d, 0x33, 0x4d, 0x57,
        0x68, 0x41, 0x67, 0x4d, 0x42, 0x41, 0x41, 0x47, 0x6a, 0x61, 0x7a, 0x42,
        0x70, 0x4d, 0x41, 0x6b, 0x47, 0x41, 0x31, 0x55, 0x64, 0x45, 0x77, 0x51,
        0x43, 0x4d, 0x41, 0x41, 0x77, 0x0a, 0x43, 0x77, 0x59, 0x44, 0x56, 0x52,
        0x30, 0x50, 0x42, 0x41, 0x51, 0x44, 0x41, 0x67, 0x58, 0x67, 0x4d, 0x45,
        0x38, 0x47, 0x41, 0x31, 0x55, 0x64, 0x45, 0x51, 0x52, 0x49, 0x4d, 0x45,
        0x61, 0x43, 0x45, 0x43, 0x6f, 0x75, 0x64, 0x47, 0x56, 0x7a, 0x64, 0x43,
        0x35, 0x6e, 0x62, 0x32, 0x39, 0x6e, 0x62, 0x47, 0x55, 0x75, 0x5a, 0x6e,
        0x4b, 0x43, 0x47, 0x48, 0x64, 0x68, 0x64, 0x47, 0x56, 0x79, 0x0a, 0x65,
        0x6d, 0x39, 0x76, 0x61, 0x53, 0x35, 0x30, 0x5a, 0x58, 0x4e, 0x30, 0x4c,
        0x6d, 0x64, 0x76, 0x62, 0x32, 0x64, 0x73, 0x5a, 0x53, 0x35, 0x69, 0x5a,
        0x59, 0x49, 0x53, 0x4b, 0x69, 0x35, 0x30, 0x5a, 0x58, 0x4e, 0x30, 0x4c,
        0x6e, 0x6c, 0x76, 0x64, 0x58, 0x52, 0x31, 0x59, 0x6d, 0x55, 0x75, 0x59,
        0x32, 0x39, 0x74, 0x68, 0x77, 0x54, 0x41, 0x71, 0x41, 0x45, 0x44, 0x4d,
        0x41, 0x30, 0x47, 0x0a, 0x43, 0x53, 0x71, 0x47, 0x53, 0x49, 0x62, 0x33,
        0x44, 0x51, 0x45, 0x42, 0x43, 0x77, 0x55, 0x41, 0x41, 0x34, 0x47, 0x42,
        0x41, 0x4a, 0x46, 0x58, 0x56, 0x69, 0x66, 0x51, 0x4e, 0x75, 0x62, 0x31,
        0x4c, 0x55, 0x50, 0x34, 0x4a, 0x6c, 0x6e, 0x58, 0x35, 0x6c, 0x58, 0x4e,
        0x6c, 0x6f, 0x38, 0x46, 0x78, 0x5a, 0x32, 0x61, 0x31, 0x32, 0x41, 0x46,
        0x51, 0x73, 0x2b, 0x62, 0x7a, 0x6f, 0x4a, 0x36, 0x0a, 0x68, 0x4d, 0x30,
        0x34, 0x34, 0x45, 0x44, 0x6a, 0x71, 0x79, 0x78, 0x55, 0x71, 0x53, 0x62,
        0x56, 0x65, 0x50, 0x4b, 0x30, 0x6e, 0x69, 0x33, 0x77, 0x31, 0x66, 0x48,
        0x51, 0x42, 0x35, 0x72, 0x59, 0x39, 0x79, 0x59, 0x43, 0x35, 0x66, 0x38,
        0x47, 0x37, 0x61, 0x71, 0x71, 0x54, 0x59, 0x31, 0x51, 0x4f, 0x68, 0x6f,
        0x55, 0x6b, 0x38, 0x5a, 0x54, 0x53, 0x54, 0x52, 0x70, 0x6e, 0x6b, 0x54,
        0x68, 0x0a, 0x79, 0x34, 0x6a, 0x6a, 0x64, 0x76, 0x54, 0x5a, 0x65, 0x4c,
        0x44, 0x56, 0x42, 0x6c, 0x75, 0x65, 0x5a, 0x55, 0x54, 0x44, 0x52, 0x6d,
        0x79, 0x32, 0x66, 0x65, 0x59, 0x35, 0x61, 0x5a, 0x49, 0x55, 0x31, 0x38,
        0x76, 0x46, 0x44, 0x4b, 0x30, 0x38, 0x64, 0x54, 0x47, 0x30, 0x41, 0x38,
        0x37, 0x70, 0x70, 0x70, 0x75, 0x76, 0x31, 0x4c, 0x4e, 0x49, 0x52, 0x33,
        0x6c, 0x6f, 0x76, 0x65, 0x55, 0x38, 0x0a, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d,
        0x45, 0x4e, 0x44, 0x20, 0x43, 0x45, 0x52, 0x54, 0x49, 0x46, 0x49, 0x43,
        0x41, 0x54, 0x45, 0x2d, 0x2d, 0x2d, 0x2d, 0x2d, 0x0a, 0x00 };
