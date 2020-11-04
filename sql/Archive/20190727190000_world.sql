DROP PROCEDURE IF EXISTS add_migration;
delimiter ??
CREATE PROCEDURE `add_migration`()
BEGIN
DECLARE v INT DEFAULT 1;
SET v = (SELECT COUNT(*) FROM `migrations` WHERE `id`='20190727190000');
IF v=0 THEN
INSERT INTO `migrations` VALUES ('20190727190000');

REPLACE INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
('-1999927', 'You are NOT PREPEARED!!!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Вы НЕ ГОТОВЫ!!!', '0', '6', '0', '0', 'CUSTOM_FELGUARD_SAY'),
('-1999928', 'You\'ll regret approaching me, mortal!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Ты пожалеешь, что приблизился ко мне, смертный!', '0', '6', '0', '0', 'CUSTOM_FELGUARD_SAY'),
('-1999929', 'Kazzak has cleared our path. This world is doomed, foolish mortals.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Каззак расчистил наш путь. Этот мир обречён, глупые смертные.', '0', '6', '0', '0', 'CUSTOM_FELGUARD_SAY'),
('-1999930', 'The Dark Portal calls. You cannot stop us!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Тёмный Портал зовёт. Вы не можете остановить нас!', '0', '6', '0', '0', 'CUSTOM_FELGUARD_SAY'),
('-1999931', 'Surrender your world to us. This invasion cannot be stopped!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Оставь свой мир нам. Это вторжение не остановить!', '0', '6', '0', '0', 'CUSTOM_FELGUARD_SAY'),
('-1999932', 'Our lord Sargeras grows impatient. Your fates are sealed!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, 'Владыка Саргерас теряет терпение. Ваши судьбы предопределены!', '0', '6', '0', '0', 'CUSTOM_FELGUARD_SAY');

END IF;
END??
delimiter ; 
CALL add_migration();
DROP PROCEDURE IF EXISTS add_migration;
