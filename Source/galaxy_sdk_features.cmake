cmake_minimum_required(VERSION 3.12)

# these are prefixed with GALAXY_BUILD_FEATURE_
function(add_feature_definitions_to_target TARGET MAJOR MINOR PATCH)
  set(BUILD_FEATURES_LIST_ENABLED "")
  set(BUILD_FEATURES_LIST_DISABLED "")

  set(UVV "${MAJOR}.${MINOR}.${PATCH}")

  #		NAME							START_VERSION END_VERSION
  afvd(HAS_IGALAXY	 							1.57.0 		1.114.9		)
  afvd(HAS_ISERVERNETWORKING		        	1.57.0		1.134.10	)

  afvd(IFRIENDS_HAS_PERSONANAME_AND_AVATARURL	1.59.0					)

  afvd(IFRIENDS_ONPERSONADATACHANGED			1.61.0					)
  afvd(IFRIENDS_SET_DEL_CLR_RICHPRESENCE		1.61.0					)
  afvd(HAS_IRICHPRECENSECHANGELISTENER			1.61.0					)

  afvd(HAS_IERRORMANAGER						1.62.0					)
  afvd(FACTORY_RESET_RENAMED_TO_RESETINSTANCE	1.62.0					)
  afvd(LEADERBOARDENTRY_REASON_NOT_FOUND		1.62.0					)
  afvd(IUSER_HAS_ISLOGGEDON						1.62.0					)

  afvd(HAS_GAMEJOINREQUESTEDLISTENER			1.65.0					)
  afvd(HAS_OPERATIONALSTATECHANGELISTENER		1.65.0					)

  afvd(FACTORY_HAS_CALLTYPE 					1.67.0 					)
  afvd(ENCRYPTED_APP_TICKET 					1.67.0 					)
  afvd(HAS_IFRIENDLISTLISTENER 					1.67.0 					)
  afvd(HAS_IOVERLAYSTATECHANGELISTENER  		1.67.0 		1.132.1		)

  afvd(HAS_GETLEADERBORDENTRYCOUNT				1.68.0 					)

  afvd(HAS_LEADERBOARD_WITH_DETAILS	    		1.69.0 					)

  afvd(HAS_ILEADERBOARDRETRIEVELISTENER    		1.70.0 					)
  afvd(HAS_IACCESSTOKENLISTENER         		1.70.0 					)
  afvd(HAS_SIGNIN_WITH_SERVERKEY         		1.70.0 					)

  afvd(HAS_GALAXYID_GETREALID            		1.71.0 					)
  afvd(IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY  1.71.0 					)
  afvd(IMATCHMAKING_GET_DATA_MEMBER_COPY        1.71.0 					)
  afvd(ISTATS_LEADERBORDSORTMETHOD_1_71_ARG_CHANGE 1.71.0 	1.72.0		)
  afvd(ISTATS_GET_ACHIEVEMENT_LEADERBOARD_COPY	1.71.0 			    	)
  afvd(IUSER_GET_DATA_ACCESSTOKEN_COPY          1.71.0 			    	)

  afvd(HAS_IUTILS	                            1.73.0 			    	)
  afvd(HAS_IAPPS	                            1.73.0 			    	)
  afvd(HAS_SPECIFICUSERDATALISTENER   		    1.73.0 			    	)
  afvd(HAS_ISENDINVITATIONLISTENER   		    1.73.0 			    	)
  afvd(HAS_IUSERTIMEPLAYEDRETRIEVELISTENER		1.73.0					)
  afvd(HAS_1_73_AVATARTYPE_CRITERIA				1.73.0					)
  afvd(HAS_1_73_LOBBY_FEATURES					1.73.0					)

  afvd(ADDED_RICH_PRESENCE_LISTENERS			1.74.0					)
  
  # up to here it's up-to-date

  afvd(HAS_INOTIFICATIONLISTENER        		1.75.0 					)
  afvd(HAS_ILOBBYDATARETRIEVELISTENER      		1.75.0 					)
  afvd(HAS_IGAMEINVITATIONRECEIVEDLISTENER 		1.75.0 					)
  afvd(IFRIENDS_HAS_ISAVATARRGBAIMAGEAVAILABLE 	1.75.0 					)
  afvd(HAS_IFRIEND_ISAVATARAVAILABLE			1.75.0					)

  afvd(HAS_IUSERTIMEPLAYEDRETRIEVELISTENER_UPDATE 1.76.0				)
  afvd(HAS_IUTILS_SHOWOVERLAYWITHWEBPAGE		1.76.0					)
  
  afvd(HAS_SIGNIN_PS4							1.77.0		1.132.1		)
  afvd(HAS_SIGNIN_REQUIREONLINE					1.77.0					)

  afvd(HAS_PERSONASTATE_ENUM					1.78.0					)
  afvd(HAS_LOBBYTOPOLOGYTYPE_ENUM				1.78.0					)
  afvd(HAS_P2P_SEND_IMMEDIATE					1.78.0					)

  afvd(HAS_INITOPTIONS 							1.82.0 					)
  afvd(HAS_IOTHERSESSIONSTARTLISTENER			1.82.0 					)
  afvd(HAS_REQUESTLOBBYLIST_ARGS_ALLOWFULL		1.82.0 					)
  afvd(HAS_INITOPTIONS_GALAXYPEERPATH      		1.82.0 		1.120.0 	)
  afvd(HAS_SIGNIN_CLASSIC_XBOX					1.82.0		1.132.1		)

  afvd(HAS_ISTORAGE 							1.88.0 					)
  afvd(HAS_GETCURRENTGAMELANGUAGE				1.88.0 					)
  afvd(HAS_ISTORAGE_SYNCHRONIZE					1.88.0 		1.99.0		)

  afvd(IUTILS_NOTIFICATION_ID_TYPEDEF   		1.92.1					)

  afvd(HAS_ICUSTOMNETWORKING					1.99.0 					)

  afvd(ENCRYPTED_APP_TICKET_CONST 				1.102.0					)

  afvd(OVERLAYSTATE_ENUM 						1.103.0					)

  afvd(HAS_ICHAT 								1.104.3					)
  afvd(NEW_FRIEND_FEATURES_104_3				1.104.3					)
  afvd(HAS_ICHAT_ROOMID_IN_INDEX				1.104.3		1.104.3		)

  afvd(HAS_FRIENDADDLISTENER					1.104.4					)
  afvd(HAS_IFRIEND_INVITEEXTRAFAILREASONS		1.104.4					)

  afvd(GALAXYID_HAS_IDTYPE 						1.106.0					)

  afvd(HAS_DISABLEOVERLAYPOPUPS 				1.109.0					)
  afvd(FIND_USER 								1.109.0					)
  afvd(HAS_ICHATROOMMESSAGERETRIEVELISTENER		1.109.0					)
  afvd(HAS_IUSERFINDLISTENER            		1.109.0					)

  afvd(HAS_ICHAT_MESSAGETYPE            		1.110.0					)

  afvd(HAS_NAT_FUNCTIONALITY 					1.113.0					)
  afvd(HAS_USERDATAINFOAVAILABLE 				1.113.2					)
  afvd(SEND_LOBBY_MESSAGE_CHAR_TO_VOID 			1.113.3					)

  afvd(HAS_CONNECTION_TYPE 						1.114.0					)
  afvd(GetImageRGBA_CHAR_TO_VOID 				1.114.0					)
  afvd(HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER 1.114.0			)

  afvd(HAS_INITOPTIONS_MODERN 					1.120.0					)
  afvd(ALLOCATOR 								1.120.0					)
  afvd(EXCEPTION_HELPER 						1.120.0					)
  afvd(GAME_SERVER_API 							1.120.0					)
  afvd(NEEDS_DLL_IMPL 							1.120.0					)
  afvd(HAS_GAMESERVERSERVERNETWORKINGLISTENER	1.120.1		1.134.10	)

  afvd(USER_SIGNIN_LISTENERS 					1.121.3					)

  afvd(HAS_INITOPTIONS_STORAGEPATH				1.122.0					)

  afvd(LOBBY_LISTENERS 							1.125.0					)
  afvd(MATCHMAKING_RET_TYPE_VOID 				1.125.0					)
  afvd(USER_DATA_LISTENERS 						1.125.0					)
  afvd(USER_SIGNIN_CROSSPLATFORM 				1.125.0					)

  afvd(HAS_IUSER_CONST_LISTENERS				1.125.0					)
  afvd(ISTATS_UPDATE_1_125						1.125.0					)

  afvd(HAS_LISTENERTYPE							1.125.1					)

  afvd(IFRIENDS_INFORMATIONLISTENERS			1.126.0					)

  afvd(IFRIENDS_ISTATS_UPDATE_1_127_0			1.127.0					)

  afvd(HAS_ISUSERINTHESAMEGAME					1.128.0					)

  afvd(HAS_CONNECTION_FAILURE_REASON		    1.129.0					)
  afvd(HAS_IMATCHMAKING_LOBBY_LIST_RESULT		1.129.0					)
  afvd(IUTILS_GETNOTIFICATION_1_129_CHANGE		1.129.0					)

  afvd(USER_ACCESS_TOKEN_INFO 					1.131.0					)
  afvd(MATCHMAKING_RESULT_COUNT 				1.131.0					)

  afvd(HAS_INITOPTIONS_HOST_PORT				1.132.0					)

  afvd(HAS_GAMESERVER_UTILS						1.133.0					)
  afvd(HAS_GOGSERVICECONNECTIONSTATELISTENER	1.133.0					)
  afvd(HAS_IMATCHMAKING_LOBBY_LEAVE_REASON		1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINCREDENTIALS		1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINSTEAM			1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINGALAXY			1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINPS4	    		1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINXB1	    		1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINSERVERKEY		1.133.0					)
  afvd(HAS_SIGNINTOKEN							1.133.0					)
  afvd(HAS_SIGNINUWP							1.133.0		1.148.4		)
  afvd(HAS_SIGNINXB1							1.133.0					)

  afvd(HAS_SIGNOUT								1.133.1					)

  afvd(HAS_GAMESERVERGLOBALGOGSERVICESCONNECTIONSTATELISTENER	1.133.3	)

  afvd(HAS_IUTILS_AUTHLOST		 				1.133.6					) 

  afvd(HAS_ITELEMETRY			 				1.134.0					) 

  afvd(HAS_GAMESERVERTELEMETRY	 				1.134.9		1.134.10	) 

  afvd(HAS_REQUESTUSERDATA_ISPECIFICLISTENER	1.134.10	1.134.10	) 
  afvd(HAS_ICHAT_ROOMLISTENERS					1.134.10	1.134.10	) 
  afvd(HAS_ISTORAGE_FILESHARELISTENERS			1.134.10	1.134.10	) 

  afvd(HAS_GAMESERVERNETWORKINGLISTENER			1.135.0					) 

  afvd(HAS_GAMESERVERTELEMETRY	 				1.136.0					) 
  afvd(HAS_ICHAT_ROOMLISTENERS					1.136.0					) 

  afvd(HAS_SETUSERDATA_ISPECIFICLISTENER		1.138.1					) 
  afvd(HAS_ICONNECTIONLISTENERS					1.138.1					) 
  afvd(HAS_ISTORAGE_FILESHARELISTENERS			1.138.1					) 
  afvd(HAS_REQUESTUSERDATA_ISPECIFICLISTENER	1.138.1					) 

  afvd(IUSER_SIGNINEPIC							1.139.5		1.148.2		)

  afvd(ITELEMETRY_1_139_6_UPDATE				1.139.6					)

  afvd(ITELEMETRY_1_139_7_UPDATE				1.139.7					)

  afvd(HAS_IGALAXYTHREADFACTORY 				1.140.0					)

  afvd(HAS_ITELEMETRY_SAMPLING_CLASS			1.141.0					)
  afvd(IGALAXYTHREAD_JOINABLE_DETACH			1.141.0					)

  afvd(IUSER_SIGNINXBLIVE						1.143.0					)

  afvd(IUSER_SIGNINLAUNCHER						1.146.0					)

# from here onwards it's also up-to-date 100%

  afvd(HAS_GETRICHPRESENCEKEYBYINDEX			1.148.2					)

  afvd(IUSER_UWP_TO_XBOX_RENAME					1.148.5					)

  afvd(HAS_ICLOUDSTORAGE						1.148.6					)
  afvd(HAS_ICLOUDSTORAGE_METADATAIDX_FUNCS		1.148.6		1.148.12	)

  afvd(HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP		1.148.7					)
  afvd(HAS_IUSER_REFRESHTOKEN					1.148.7					)

  afvd(HAS_ICLOUDSTORAGE_GETFILEHASHBYINDEX		1.148.11				)

  afvd(HAS_ICLOUDSTORAGE_SAVEGAME				1.148.14				)

  afvd(HAS_ICLOUDSTORAGE_HASHING				1.148.15				) # this version should be binary compatible up to and including 1.149.0, and also 1.150.0!

  afvd(HAS_INITOPTIONS_GAMESERVICEPLATFORM		1.149.1		1.149.16	)

  afvd(HAS_IUSER_REPORTGAMEOWNERSHIP			1.149.2		1.149.16	)

  afvd(HAS_GAMERSERVICEPLATFORM_TOKEN			1.149.9		1.149.16	)

  afvd(HAS_GAMERSERVICEPLATFORM_TOKEN_LENGTH	1.149.10	1.149.16	)

  afvd(HAS_ITELEMETRY_GENERATEUUIDSTR			1.149.11	1.149.16	)

  afvd(HAS_RED_PREFIX							1.149.12	1.149.16	)

  afvd(HAS_SHUTDOWNOPTIONS						1.151.0					)
  afvd(HAS_IAPPS_LANGUAGECODE					1.151.0					)
  
  afvd(HAS_IUSER_AUTHORIZATION_IDTOKEN			1.152.1					)

  afvd(HAS_IAPPS_ISDLCOWNED						1.152.2					)

  afvd(HAS_IUSER_OPENID							1.152.5					)

  afvd(HAS_IUSER_SIGNINGALAXY_TIMEOUT			1.152.8					)

  afvd(HAS_ISTATS_ACHIEVEMENTSNUMBER			1.152.10				)

  afvd(NEAR_FILTER_ENUM 						9.999.0					) # disabled because it's not really present? bug in SDK?
  
  afvd_finalize()
endfunction()

# INCLUSIVE MIN_VERSION and INCLUSIVE MAX_VERSION
function(afvd FEATURE_NAME FEATURE_MIN_VERSION)  
  set(RESULT 0)

  if(${UVV} VERSION_GREATER_EQUAL ${FEATURE_MIN_VERSION})
    set(RESULT 1)
  endif()

  if(ARGN)
    list (GET ARGN 0 FEATURE_MAX_VERSION)
    if(NOT "${FEATURE_MAX_VERSION}" STREQUAL "")
      if(${UVV} VERSION_GREATER ${FEATURE_MAX_VERSION})
        set(RESULT 0)
      endif()
    endif()
  endif()

  if(RESULT GREATER 0)
    if (NOT ${FEATURE_NAME} IN_LIST BUILD_FEATURES_LIST_ENABLED)
      list(APPEND BUILD_FEATURES_LIST_ENABLED ${FEATURE_NAME})
    endif()
    if (${FEATURE_NAME} IN_LIST BUILD_FEATURES_LIST_DISABLED)
      list(REMOVE_ITEM BUILD_FEATURES_LIST_DISABLED ${FEATURE_NAME})
    endif()
  else()
    if (NOT ${FEATURE_NAME} IN_LIST BUILD_FEATURES_LIST_ENABLED)
      list(APPEND BUILD_FEATURES_LIST_DISABLED ${FEATURE_NAME})
    endif()
  endif()

  set( BUILD_FEATURES_LIST_DISABLED ${BUILD_FEATURES_LIST_DISABLED} PARENT_SCOPE )
  set( BUILD_FEATURES_LIST_ENABLED ${BUILD_FEATURES_LIST_ENABLED} PARENT_SCOPE )
endfunction()

# INCLUSIVE MIN_VERSION and INCLUSIVE MAX_VERSION
function(afvd_finalize)  
  foreach(FEATURE_NAME IN LISTS BUILD_FEATURES_LIST_ENABLED)
    target_compile_definitions(${TARGET} PUBLIC 
      "GALAXY_BUILD_FEATURE_${FEATURE_NAME}=1"
    )

    set_property(GLOBAL PROPERTY "GALAXY_${UVV}_BUILD_FEATURE_${FEATURE_NAME}" "1")
  endforeach()

  foreach(FEATURE_NAME IN LISTS BUILD_FEATURES_LIST_DISABLED)
    target_compile_definitions(${TARGET} PUBLIC 
      "GALAXY_BUILD_FEATURE_${FEATURE_NAME}=0"
    )

    set_property(GLOBAL PROPERTY "GALAXY_${UVV}_BUILD_FEATURE_${FEATURE_NAME}" "0")
  endforeach()
endfunction()
