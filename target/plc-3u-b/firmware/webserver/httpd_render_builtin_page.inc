			while((char *)pgm_read_word(&WEBPAGE_TABLE[page_index].filename))
			{
				if (strcasestr_P((char*)&eth_buffer[TCP_DATA_START_VAR],(char *)pgm_read_word(&WEBPAGE_TABLE[page_index].filename))!=0) 
					{
					char fname[12];
					strncpy_P(fname,(char *)pgm_read_word(&WEBPAGE_TABLE[page_index].filename),12);
					http_entry[index].http_header_type = 1;
					if (strcasestr_P(fname,PSTR(".htm"))!=0) {
						http_entry[index].http_header_type = 0;	
					}	
					else if (strcasestr_P(fname,PSTR(".jpg"))!=0) {
						#if USE_CAM
						if (strcasestr_P(fname,PSTR("camera"))!=0)
						{	
							http_entry[index].cam = 1;
						}
						#endif //USE_CAM
						http_entry[index].http_header_type = 1;
					}
					else if (strcasestr_P(fname,PSTR(".gif"))!=0) {
						http_entry[index].http_header_type = 1;
					}

					http_entry[index].new_page_pointer = (char *)pgm_read_word(&WEBPAGE_TABLE[page_index].page_pointer);
					break;
				}
				page_index++;
			}
