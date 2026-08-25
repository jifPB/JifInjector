#pragma once

namespace Jif
{
	namespace Settings
	{
		class JifSettings
		{
		public:
			static JifSettings &GetInstance()
			{
				static JifSettings instance;
				return instance;
			}

			JifSettings(const JifSettings &) = delete;
			JifSettings(const JifSettings &&) = delete;
			JifSettings &operator=(const JifSettings &) = delete;
			JifSettings &operator=(const JifSettings &&) = delete;

		private:
			JifSettings() = default;
			~JifSettings() = default;
		};
	}
}
