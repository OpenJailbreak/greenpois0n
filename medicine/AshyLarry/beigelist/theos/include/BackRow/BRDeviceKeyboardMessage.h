/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/BackRow.framework/BackRow
 */


@class NSString;

@interface BRDeviceKeyboardMessage : NSObject {
@private
	NSString *_string;	// 4 = 0x4
	NSString *_title;	// 8 = 0x8
	NSString *_subText;	// 12 = 0xc
	unsigned long long _sessionID;	// 16 = 0x10
	int _msgType;	// 24 = 0x18
	int _keyboardType;	// 28 = 0x1c
	BOOL _secureText;	// 32 = 0x20
	unsigned _version;	// 36 = 0x24
}
@property(assign) int keyboardType;	// G=0x3163d419; S=0x3163d429; converted property
@property(assign) int msgType;	// G=0x3163d3f9; S=0x3163d409; converted property
@property(assign) BOOL secureText;	// G=0x3163d47d; S=0x3163d48d; converted property
@property(assign) unsigned long long sessionID;	// G=0x3163d439; S=0x3163d449; converted property
@property(retain) NSString *string;	// G=0x3163d3c9; S=0x3163d779; converted property
@property(retain) NSString *subText;	// G=0x3163d3e9; S=0x3163d709; converted property
@property(retain) NSString *title;	// G=0x3163d3d9; S=0x3163d741; converted property
@property(assign) unsigned version;	// G=0x3163d45d; S=0x3163d46d; converted property
+ (id)_dictionaryArraytoDictionary:(id)dictionary;	// 0x3163d519
+ (id)_keyValueToDictionary:(id)dictionary key:(id)key;	// 0x3163d49d
+ (id)dictionaryToDictionaryArray:(id)dictionaryArray;	// 0x3163d605
+ (id)messageFromDictionary:(id)dictionary;	// 0x3163d9a1
+ (id)messageFromDictionaryArray:(id)dictionaryArray;	// 0x3163db71
+ (unsigned long)vendNewSessionID;	// 0x3163d3b9
- (void)dealloc;	// 0x3163dba5
- (id)dictionary;	// 0x3163d7b1
- (id)dictionaryArray;	// 0x3163d96d
// converted property getter: - (int)keyboardType;	// 0x3163d419
// converted property getter: - (int)msgType;	// 0x3163d3f9
// converted property getter: - (BOOL)secureText;	// 0x3163d47d
// converted property getter: - (unsigned long long)sessionID;	// 0x3163d439
// converted property setter: - (void)setKeyboardType:(int)type;	// 0x3163d429
// converted property setter: - (void)setMsgType:(int)type;	// 0x3163d409
// converted property setter: - (void)setSecureText:(BOOL)text;	// 0x3163d48d
// converted property setter: - (void)setSessionID:(unsigned long long)anId;	// 0x3163d449
// converted property setter: - (void)setString:(id)string;	// 0x3163d779
// converted property setter: - (void)setSubText:(id)text;	// 0x3163d709
// converted property setter: - (void)setTitle:(id)title;	// 0x3163d741
// converted property setter: - (void)setVersion:(unsigned)version;	// 0x3163d46d
// converted property getter: - (id)string;	// 0x3163d3c9
// converted property getter: - (id)subText;	// 0x3163d3e9
// converted property getter: - (id)title;	// 0x3163d3d9
// converted property getter: - (unsigned)version;	// 0x3163d45d
@end

