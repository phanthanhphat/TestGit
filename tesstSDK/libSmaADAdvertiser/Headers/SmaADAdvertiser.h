//
//  SmaADAdvertiser.h
//  SmaADAdvertiser
//
//  Created by 迫田 雅弘 on 2014/02/10.
//  Copyright (c) 2014年 GMO Tech Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SmaADAdvertiserDelegate;

typedef NS_ENUM(NSUInteger, SmaADMultipleConversionType) {
    SmaADMultipleConversionTypeLTV,
    SmaADMultipleConversionTypeDaily,
    SmaADMultipleConversionTypeFrequency,
    SmaADMultipleConversionTypeInAppPurchase
};

typedef NS_ENUM(NSUInteger, SmaADLTVConversionType) {
    SmaADLTVConversionTypeLTV1,
    SmaADLTVConversionTypeLTV2,
    SmaADLTVConversionTypeLTVWithdrawal
};

@interface SmaADAdvertiser : NSObject

// 広告主アカウントID
@property (nonatomic) NSString *accountID;
// AppStoreのID(itunes.apple.comのidxxxxxxxxx部分)
@property (nonatomic) NSString *appStoreID;
// サイトオープンの場合はURL, リダイレクトの場合はURL Scheme("://"は不要)
@property (nonatomic) NSString *urlString;
// 二重成果チェックをするか
@property (nonatomic) BOOL checkDuplicateConversion;
// 自然流入チェックをするか
@property (nonatomic) BOOL checkNaturallyInstallation;

/**
 *  成果送信イベントを受け取るデリゲート
 *  SmaADAdvertiserDelegateプロトコルを参照
 */
@property (nonatomic) id<SmaADAdvertiserDelegate> delegate;

/**
 *  初回成果送信実行
 */
- (void)runInitialConversion;

/**
 *  LTV成果送信実行
 *
 *  @param ltvScene 管理画面で設定した成果地点名
 */
- (void)runLTVConversionWithType:(SmaADLTVConversionType)ltvType;

/**
 *  日別多段階成果送信実行
 */
- (void)runDailyConversion;

/**
 *  回数別多段階成果送信実行
 */
- (void)runFrequencyConversion;

/**
 *  課金別多段階成果送信実行
 *  @param purchaseType 課金別多段階成果計測における成果識別ID
 */
- (void)runIAPConversion:(NSUInteger)purchaseType;

@end

@protocol SmaADAdvertiserDelegate <NSObject>
@optional
/**
 *  初回成果送信成功時
 */
- (void)didSuccessSendingInitialConversion;
/**
 *  初回成果送信失敗時
 *  @param error エラーオブジェクト
 */
- (void)didFailSendingInitialConversionWithError:(NSError *)error;
/**
 *  初回成果送信処理終了時
 */
- (void)didCompleteExecuteInitialConversion;

/**
 *  LTV/多段階成果送信成功時
 *  @param conversionType 成果タイプ(LTV/日別/回数別/課金別)
 */
- (void)didSuccessSendingMultipleConversion:(SmaADMultipleConversionType)conversionType;
/**
 *  LTV/多段階成果送信失敗時
 *  @param conversionType 成果タイプ(LTV/日別/回数別/課金別)
 *  @param error          エラーオブジェクト
 */
- (void)didFailSendingMultipleConversion:(SmaADMultipleConversionType)conversionType withError:(NSError *)error;
/**
 *  LTV/多段階成果処理終了時
 *  @param conversionType 成果タイプ(LTV/日別/回数別/課金別)
 */
- (void)didCompleteExecuteMultipleConversion:(SmaADMultipleConversionType)conversionType;

@end
